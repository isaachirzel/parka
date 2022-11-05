#include <warbler/validator.h>
#include <warbler/util/print.h>
#include <warbler/scope.h>
#include <string.h>

const char *annotationTypeName(AnnotationType type)
{
	switch (type)
	{
		case ANNOTATION_STRUCT:
			return "struct";

		case ANNOTATION_PRIMITIVE:
			return "primitive";

		default:
			return "type";
	}
}

bool validateType(TypeContext *out, const TypeSyntax *syntax, SymbolTable *table)
{
	// TODO: Optimize name
	char *name = tokenGetText(&syntax->name);
	SymbolData *data = symbolTableResolve(table, name);

	if (!data)
	{
		printTokenError(&syntax->name, "The type '%s' does not exist this scope.", name);
		return false;
	}

	if (!data->isValid)
		return false;

	AnnotationType annotationType;

	switch (data->id.type)
	{
		case SYMBOL_STRUCT:
			annotationType = ANNOTATION_STRUCT;
			break;

		case SYMBOL_PRIMITIVE:
			annotationType = ANNOTATION_PRIMITIVE;
			break;

		default:
		{
			const char *typeName = getSymbolTypeName(data->id.type);
			printTokenError(&syntax->name, "Expected type name, found %s '%s'.", typeName, name);
			return false;
		}
	}

	TypeContext type =
	{
		.type = annotationType,
		.id = data->id
	};

	*out = type;
	return true;
}

bool validateStructMember(MemberContext *out, const MemberSyntax *syntax, SymbolTable *symbols, Scope *scope)
{
	MemberContext context =
	{
		.name = tokenGetText(&syntax->name),
		.isPublic = syntax->isPublic
	};

	char *typeName = tokenGetText(&syntax->type.name);
	SymbolData *data = symbolTableFindGlobal(symbols, typeName);

	if (!data)
	{
		// TODO: Search syntax tree
		printTokenError(&syntax->type.name, "Unable to find type: %s", typeName);
		goto error;
	}

	if (scopeContains(scope, data->symbol))
	{
		printTokenError(&syntax->type.name, "Member creates infinite size struct. Try using a reference or pointer.");
		goto error;
	}

	if (!validateType(&context.type, &syntax->type, symbols))
		goto error;

	*out = context;

	return true;

error:

	freeMemberContext(&context);
	return false;
}

bool validateStructDeclaration(StructContext *out, const StructSyntax *syntax, SymbolTable *table)
{
	bool success = true;
	// TODO: Stack-based identifier string
	char *identifier = tokenGetText(&syntax->name);

	out->symbol = symbolTableCreateSymbol(table, identifier);
	out->memberCount = syntax->memberCount;

	makeArray(out->members, out->memberCount);
	deallocate(identifier);

	SymbolData *data = symbolTableDeclareGlobal(table, out->symbol);

	success = success && data;

	if (data)
	{
		data-> id = (SymbolId)
		{
			.type = SYMBOL_STRUCT,
			.package = table->packageIndex,
			.module = table->moduleIndex,
			.global = table->globalIndex
		};
	}

	return success;
}

bool validateStructDefinition(StructContext *out, const StructSyntax *syntax, SymbolTable *symbols, Scope *scope)
{
	bool success = true;

	scopePush(scope, out->symbol);

	for (usize i = 0; i < syntax->memberCount; ++i)
	{
		const MemberSyntax *memberSyntax = &syntax->members[i];

		for (usize j = 0; j < i; ++j)
		{
			if (tokenIsSame(&memberSyntax->name, &syntax->members[j].name))
			{
				success = false;
				// TODO: Stack based string
				char *name = tokenGetText(&memberSyntax->name);
				printTokenError(&syntax->name, "A member with name '%s' is already declared in struct '%s'.", name, out->symbol);
				// TODO: Show previous declaration
				deallocate(name);
				// Break to avoid showing duplicate, incorrect errors
				break;
			}
		}

		success = success && validateStructMember(&out->members[i], memberSyntax, symbols, scope);
	}

	scopePop(scope);

	return success;
}

bool validateConstant(ExpressionContext *out, const ConstantSyntax *syntax)
{
	ConstantContext context =
	{
		.type = syntax->type
	};

	switch (syntax->type)
	{
		case CONSTANT_CHARACTER:
			context.character = syntax->character;
			break;

		case CONSTANT_STRING:
			context.string = duplicateString(syntax->string);
			break;

		case CONSTANT_INTEGER:
			context.integer = syntax->integer;
			break;

		case CONSTANT_FLOAT:
			context.floating = syntax->floating;
			break;

		case CONSTANT_BOOLEAN:
			context.boolean = syntax->boolean;
			break;

		default:
			exitWithErrorFmt("Invalid constant type: %d.", syntax->type);
	}

	return true;
}

bool validateSymbol(ExpressionContext *out, const SymbolSyntax *syntax, SymbolTable *symbols)
{
	bool success = true;
	char *symbol = tokenGetText(&syntax->token);
	SymbolData *data = symbolTableFind(symbols, symbol);

	if (!data)
	{
		printTokenError(&syntax->token, "The symbol '%s' could not be found in this scope.", symbol);
		success = false;
	}
	else
	{
		*makeNew(out->symbolId) = data->id;
		out->type = EXPRESSION_SYMBOL;
	}

	deallocate(symbol);
	
	return success;
}

bool validateAssignment(ExpressionContext *out, const AssignmentSyntax *syntax, SymbolTable *symbols)
{
	AssignmentContext context =
	{
		.type = syntax->type
	};

	bool success = true;

	success = success && validateExpression(&context.lhs, &syntax->lhs, symbols);
	success = success && validateExpression(&context.rhs, &syntax->rhs, symbols);

	// TODO: validate type of assignment

	if (!success)
	{
		freeAssignmentContext(&context);
		return false;
	}

	*makeNew(out->assignment) = context;
	out->type = EXPRESSION_ASSIGNMENT;

	return true;
}

bool validateBlock(ExpressionContext *out, const BlockSyntax *syntax, SymbolTable *symbols)
{
	bool success = true;
	BlockContext context =
	{
		.count = syntax->count
	};

	makeArray(context.statements, syntax->count);

	for (usize i = 0; i < syntax->count; ++i)
		success = success && validateStatement(&context.statements[i], &syntax->statements[i], symbols);

	if (!success)
		goto error;

	*makeNew(out->block) = context;
	out->type = EXPRESSION_BLOCK;

	return true;

error:

	freeBlockContext(&context);
	return false;
}

bool validateExpression(ExpressionContext *out, const ExpressionSyntax *syntax, SymbolTable *symbols)
{
	switch (syntax->type)
	{
		case EXPRESSION_BLOCK:
			return validateBlock(out, syntax->block, symbols);

		case EXPRESSION_CONSTANT:
			return validateConstant(out, syntax->constant);

		case EXPRESSION_SYMBOL:
			return validateSymbol(out, syntax->symbol, symbols);

		case EXPRESSION_ASSIGNMENT:
			return validateAssignment(out, syntax->assignment, symbols);

		default:
			exitWithErrorFmt("Invalid expression type: %d.", syntax->type);
	}
}

static bool validateStructConversion(const Token *token, const TypeContext *to, const TypeContext *from, const SymbolTable *globals)
{
	exitNotImplemented();

	// assert(to->type == ANNOTATION_STRUCT);
	// assert(from->type == ANNOTATION_STRUCT);
}

static bool validateConstantToPrimitiveConversion(const TypeContext *to, const TypeContext *from, const SymbolTable *globals)
{
	exitNotImplemented();
}

static bool validatePrimitiveConversion(const TypeContext *to, const TypeContext *from, const SymbolTable *globals)
{
	exitNotImplemented();
	// assert(to.type() == ANNOTATION_PRIMITIVE);
	
	// if (from.type() == ANNOTATION_STRUCT)
	// {
	// 	printError("Unable to convert from struct to primitive");
	// 	return false;
	// }

	// if (from.type() == ANNOTATION_CONSTANT)
	// 	return validateConstantToPrimitiveConversion(to, from, globals);

	// const auto *left = globals.primitiveAt(to.index());
	// const auto *right = globals.primitiveAt(from.index());

	// if (left.type() != right.type())
	// {
	// 	printInvalidConversionError(to, from, globals);

	// 	return false;
	// }

	// // TODO: Figure out how the interactions would work if 'to' is a literal, or how that would even happen
	// // Assumedly 1 = 1; or something like that

	// switch (left.type())
	// {
	// 	case PRIMITIVE_UNSIGNED_INTEGER:

	// 		if (left.integer().isSigned() != right.integer().isSigned()  *right.size() != 0)
	// 		{
	// 			const char *leftSigned = getSignedLabel(left.integer());
	// 			const char *rightSigned = getSignedLabel(right.integer());

	// 			printError("Unable to assign " + rightSigned + " integer to " + leftSigned + " integer");
	// 			return false;
	// 		}

	// 	case PRIMITIVE_FLOATING_POINT:
	// 		if (left.size() == 0)
	// 		{
	// 			printError("Unable to assign to '" + left.symbol() + "' as it is a temporary value.");
	// 			return false;
	// 		}

	// 		if (right.size() == 0)
	// 			return true;

	// 		if (left.size() != right.size())
	// 		{
	// 			printError("Unable to assign value of type '" + right.symbol() + "' to a value of type '" + left.symbol() + "' as it reduces precision.");
	// 			return false;
	// 		}

	// 		return true;

	// 	case PRIMITIVE_BOOLEAN:
	// 	case PRIMITIVE_CHARACTER:
			

	// 		return true;

	// 	default:
	// 		throw std::invalidArgument("Invalid primitive type for conversion");
	// }
}

static const char *getConstantTypeName(ConstantType type)
{
	switch (type)
	{
		case CONSTANT_CHARACTER:
			return "char";

		case CONSTANT_STRING:
			return "string literal";
			
		case CONSTANT_INTEGER:
			return "integer";

		case CONSTANT_FLOAT:
			return "float";

		case CONSTANT_BOOLEAN:
			return "bool";

		default:
			exitWithErrorFmt("Invalid constant type: %d.", type);
	}
}

static TypeContext getExpressionType(const ExpressionContext *expression, SymbolTable *symbols)
{
	exitNotImplemented();
}

static bool validateExpressionConversion(TypeContext *out, SymbolTable *symbols, const ExpressionContext *from, const TypeContext *to)
{
	exitNotImplemented();
}

bool validateVariable(const VariableSyntax *syntax, const ExpressionContext *value, SymbolTable *table)
{
	bool success = true;

	// TODO: maybe optimize
	ProgramContext *program = table->program;
	PackageContext *package = &program->packages[table->packageIndex];
	ModuleContext *module = &package->modules[table->moduleIndex];
	FunctionContext *function = &module->functions[table->globalIndex];

	table->localIndex = function->variableCount;
	resizeArray(function->variables, ++function->variableCount);

	VariableContext *context = &function->variables[table->localIndex];

	*context = (VariableContext)
	{
		.name = tokenGetText(&syntax->name),
		.isExplicitlyTyped = syntax->isExplicitlyTyped,
		.isMutable = syntax->isMutable
	};

	if (syntax->isExplicitlyTyped)
	{
		success = success && validateType(&context->type, &syntax->type, table);
	}
	else
	{
		context->type = getExpressionType(value, table);
	}

	SymbolData *data = symbolTableDeclareLocal(table, &syntax->name);

	success = success && data;

	if (data)
	{
		data->id = (SymbolId)
		{
			.type = SYMBOL_VARIABLE,
			.package = table->packageIndex,
			.module = table->moduleIndex,
			.global = table->globalIndex,
			.local = table->localIndex
		};
	}

	return success;
}

bool validateDeclaration(DeclarationContext *out, const DeclarationSyntax *syntax, SymbolTable *symbols)
{
	DeclarationContext context = { 0 };
	
	if (!validateExpression(&context.value, &syntax->value, symbols))
		goto error;

	if (!validateVariable(&syntax->variable, &context.value, symbols))
		goto error;

	*out = context;
	return true;

error:

	freeDeclarationContext(&context);
	return false;
}

bool validateStatement(StatementContext *out, const StatementSyntax *syntax, SymbolTable *symbols)
{
	if (syntax->isDeclaration)
	{
		DeclarationContext declaration;
		
		if (!validateDeclaration(&declaration, syntax->declaration, symbols))
			return false;

		*makeNew(out->declaration) = declaration;
	}
	else
	{
		ExpressionContext expression;

		if (!validateExpression(&expression, syntax->expression, symbols))
			return false;

		*makeNew(out->expression) = expression;
	}

	out->isDeclaration = syntax->isDeclaration;

	return true;
}

bool validateParameter(ParameterContext *out, const ParameterSyntax *syntax, SymbolTable *table)
{
	bool success = true;
	out->name = tokenGetText(&syntax->name);
	out->isMutable = syntax->isMutable;

	success = success && validateType(&out->type, &syntax->type, table);

	SymbolData *data = symbolTableDeclareLocal(table, &syntax->name);

	success = success && data;
	
	if (data)
	{
		data->id = (SymbolId)
		{
			.type = SYMBOL_PARAMETER,
			.package = table->packageIndex,
			.module = table->moduleIndex,
			.global = table->globalIndex,
			.local = table->localIndex
		};
	}

	return success;
}

bool validateParameterList(const ParameterListSyntax *syntax, SymbolTable *table)
{
	bool success = true;

	ProgramContext *program = table->program;
	PackageContext *package = &program->packages[table->packageIndex];
	ModuleContext *module = &package->modules[table->moduleIndex];
	FunctionContext *function = &module->functions[table->globalIndex];

	function->parameterCount = syntax->count;
	makeArray(function->parameters, function->parameterCount);

	for (usize i = 0; i < syntax->count; ++i)
	{
		ParameterContext *context = &function->parameters[table->localIndex];

		success = success && validateParameter(context, &syntax->data[i], table);
	}

	return success;
}

bool validateFunctionDeclaration(FunctionContext *out, const FunctionSyntax *syntax, SymbolTable *table)
{
	bool success = true;

	char *name = tokenGetText(&syntax->name);

	out->symbol = symbolTableCreateSymbol(table, name);

	deallocate(name);

	SymbolData *data = symbolTableDeclareGlobal(table, out->symbol);

	success = success && data;
	success = success && validateParameterList(&syntax->parameters, table);

	if (syntax->hasReturnType)
	{
		success = success && validateType(&out->returnType, &syntax->returnType, table);
	}
	else
	{
		out->returnType = (TypeContext)
		{
			.type = ANNOTATION_PRIMITIVE,
			.id = {
				.type = SYMBOL_PRIMITIVE,
				.global = VOID_INDEX
			}
		};
	}
	
	if (data)
	{
		data->id = (SymbolId)
		{
			.type = SYMBOL_FUNCTION,
			.package = table->packageIndex,
			.module = table->moduleIndex,
			.global = table->globalIndex
		};
	}

	return success;
}

bool validateFunctionDefinition(FunctionContext *out, const FunctionSyntax *syntax, SymbolTable *table, const Scope *scope)
{
	bool success = true;

	success = success && validateExpression(&out->body, &syntax->body, table);

	return success;
}

bool validateModuleDeclarations(ModuleContext *out, const ModuleSyntax *syntax, SymbolTable *table)
{
	bool success = true;

	out->functionCount = syntax->functionCount;
	out->structCount = syntax->structCount;

	makeArray(out->functions, out->functionCount);
	makeArray(out->structs, out->structCount);

	for (usize i = 0; i < out->functionCount; ++i)
	{
		table->globalIndex = i;
		success = success && validateFunctionDeclaration(&out->functions[i], &syntax->functions[i], table);
	}

	for (usize i = 0; i < out->structCount; ++i)
	{
		table->globalIndex = i;
		success = success && validateStructDeclaration(&out->structs[i], &syntax->structs[i], table);
	}

	return success;
}

bool validateModuleDefinitions(ModuleContext *out, const ModuleSyntax *syntax, SymbolTable *table)
{
	bool success = true;

	Scope scope = { 0 };

	for (usize i = 0; i < syntax->functionCount; ++i)
	{
		table->globalIndex = i;
		success = success && validateFunctionDefinition(&out->functions[i], &syntax->functions[i], table, &scope);
	}

	scopeClear(&scope);

	for (usize i = 0; i < syntax->structCount; ++i)
	{
		table->globalIndex = i;
		success = success && validateStructDefinition(&out->structs[i], &syntax->structs[i], table, &scope);
	}

	scopeDestroy(&scope);

	return success;
}

bool validatePackageDeclarations(PackageContext *out, const PackageSyntax *syntax, SymbolTable *table)
{
	bool success = true;

	out->symbol = duplicateString(syntax->name);
	out->moduleCount = syntax->moduleCount;

	makeArray(out->modules, out->moduleCount);
	
	SymbolData *data = symbolTableDeclareGlobal(table, out->symbol);

	if (!data)
	{
		printError("'%s' has already been declared.", out->symbol);
	}
	else
	{
		data->id = (SymbolId)
		{
			.type = SYMBOL_PACKAGE,
			.package = table->packageIndex
		};
	}

	for (usize i = 0; i < syntax->moduleCount; ++i)
	{
		table->moduleIndex = i;
		success = success && validateModuleDeclarations(&out->modules[i], &syntax->modules[i], table);
	}

	return success;
}

bool validatePackageDefinitions(PackageContext *out, const PackageSyntax *syntax, SymbolTable *table)
{
	bool success = true;

	for (usize i = 0; i < out->moduleCount; ++i)
	{
		table->moduleIndex = i;
		success = success && validateModuleDefinitions(&out->modules[i], &syntax->modules[i], table);
	}

	return success;
}

bool validate(ProgramContext *out, const ProgramSyntax *syntax)
{
	bool success = true;

	ProgramContext context =
	{
		.packageCount = syntax->packageCount
	};

	makeArray(context.packages, context.packageCount);

	SymbolTable table = symbolTableCreate(&context, syntax);

	// success = success & generateProgramSymbols(&table, syntax);

	for (usize i = 0; i < syntax->packageCount; ++i)
	{
		table.packageIndex = i;
		success = success && validatePackageDeclarations(&context.packages[i], &syntax->packages[i], &table);
	}

	for (usize i = 0; i < syntax->packageCount; ++i)
	{
		table.packageIndex = i;
		success = success && validatePackageDefinitions(&context.packages[i], &syntax->packages[i], &table);
	}

	if (success)
	{
		*out = context;
	}
	else
	{
		freeProgramContext(&context);
	}

	return success;
}
