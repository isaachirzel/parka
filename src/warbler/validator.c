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

bool validateType(TypeContext *out, const TypeSyntax *syntax, SymbolTable *symbolTable)
{
	char *name = tokenGetText(&syntax->name);
	SymbolData *symbol = symbolTableFind(symbolTable, name);

	if (!symbol)
	{
		printTokenError(&syntax->name, "The type '%s' does not exist this scope.", name);
		return false;
	}

	if (!symbol->isValid)
		return false;

	AnnotationType annotationType;

	switch (symbol->type)
	{
		case SYMBOL_STRUCT:
			annotationType = ANNOTATION_STRUCT;
			break;

		case SYMBOL_PRIMITIVE:
			annotationType = ANNOTATION_PRIMITIVE;
			break;

		default:
			printTokenError(&syntax->name, "Expected type name, found %s '%s'.", getSymbolTypeName(symbol->type), name);
			return false;
	}

	TypeContext type =
	{
		.type = annotationType,
		.index = symbol->index
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

bool validateStruct(StructContext *out, const StructSyntax *syntax, SymbolTable *symbols, Scope *scope)
{
	// TODO: Think about implications of allowing this struct to validate if there is a duplicate named struct
	// TODO: Stack-based identifier string
	char *identifier = tokenGetText(&syntax->name);
	char *symbol = symbolTableCreateSymbol(symbols, identifier);

	scopePush(scope, symbol);
	deallocate(identifier);

	bool success = true;

	StructContext context =
	{
		.symbol = symbol,
		.memberCount = syntax->memberCount
	};

	makeArray(context.members, context.memberCount);

	for (usize i = 0; i < syntax->memberCount; ++i)
	{
		MemberSyntax *memberSyntax = syntax->members + i;
		MemberContext *memberContext = context.members + i;

		success = success && validateStructMember(memberContext, memberSyntax, symbols, scope);

		for (usize j = 0; j < i; ++j)
		{
			if (tokenIsSame(&memberSyntax->name, &syntax->members[j].name))
			{
				success = false;
				// TODO: Stack based string
				char *name = tokenGetText(&memberSyntax->name);
				printTokenError(&syntax->name, "A member with name '%s' is already declared in struct '%s'.", name, context.symbol);
				// TODO: Show previous declaration
				deallocate(name);
				// Break to avoid showing duplicate, incorrect errors
				break;
			}
		}
	}

	scopePop(scope);

	if (success)
		success = symbolTableAddStruct(symbols, &context);

	if (!success)
		goto error;

	*out = context;

	return true;

error:
	freeStructContext(&context);
	return false;
}

bool validateParameter(usize *out, const ParameterSyntax *syntax, SymbolTable *symbols)
{
	ParameterContext context =
	{
		.name = tokenGetText(&syntax->name),
		.isMutable = syntax->isMutable
	};

	if (!validateType(&context.type, &syntax->type, symbols))
		goto error;

	usize index = symbolTableAddParameter(symbols, &context);

	if (index == SIZE_MAX)
		goto error;

	*out = index;
	return true;

error:

	freeParameterContext(&context);
	return false;
}

bool validateParameterList(ParameterListContext *out, const ParameterListSyntax *syntax, SymbolTable *symbols)
{
	ParameterListContext context =
	{
		.count = syntax->count
	};
	
	makeArray(context.data, context.count);	

	bool success = true;

	for (usize i = 0; i < syntax->count; ++i)
		success = success && validateParameter(&context.data[i], &syntax->data[i], symbols);

	if (!success)
		goto error;

	*out = context;

	return true;

error:

	freeParameterListContext(&context);
	return false;
}

bool validateFunctionSignature(FunctionSignatureContext *out, const FunctionSignatureSyntax *syntax, SymbolTable *symbols)
{
	FunctionSignatureContext context = { 0 };

	bool success = true;

	ParameterListContext parameters;
	
	success = success && validateParameterList(&parameters, &syntax->parameters, symbols);

	TypeContext returnType;

	if (syntax->hasReturnType)
	{
		TypeContext res;

		success = success && validateType(&res, &syntax->returnType, symbols);
	}

	if (!success)
	{
		freeFunctionSignatureContext(&context);
		return false;
	}

	*out = context;

	return true;
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
			exitWithError("Invalid constant type: %d.", syntax->type);
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
		SymbolContext context =
		{
			.index = data->index,
			.type = data->type
		};

		*makeNew(out->symbol) = context;
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
			exitWithError("Invalid expression type: %d.", syntax->type);
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

static bool validateConversion(const TypeContext *to, const TypeContext *from, const SymbolTable *globals)
{
	exitNotImplemented();
	// if (to.type() == ANNOTATION_CONSTANT)
	// {
	// 	printError("Cannot assign to a constant as it is a temporary value");
	// 	return false;
	// }

	// // TODO: Add pointer/reference and struct conversion
	// if (to.type() == ANNOTATION_PRIMITIVE)
	// 	return validatePrimitiveConversion(to, from, globals);

	// if (to.type() != from.type() || to.index() != from.index())
	// {
	// 	printInvalidConversionError(to, from, globals);

	// 	return false;
	// }

	// return true;
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
			exitWithError("Invalid constant type: %d.", type);
	}
}

static usize getConstantTypeIndex(ConstantType type)
{
	exitNotImplemented();
	// switch (type)
	// {
	// 	case CONSTANT_CHARACTER:
	// 		return CHAR_INDEX;

	// 	case CONSTANT_STRING:
	// 		return STRING_INDEX;

	// 	case CONSTANT_INTEGER:
	// 		return INT_INDEX;

	// 	case CONSTANT_FLOAT:
	// 		return FLOAT_INDEX;

	// 	case CONSTANT_BOOLEAN:
	// 		return BOOL_INDEX;

	// 	default:
	// 		exitWithError("Invalid constant type: %d.", type);
	// }
}

static TypeContext getConstantType(const ConstantContext *constant)
{
	usize index = getConstantTypeIndex(constant->type);
	TypeContext context =
	{
		.type = ANNOTATION_CONSTANT,
		.index = index
	};
	
	return context;
}

static TypeContext getExpressionType(const ExpressionContext *expression, SymbolTable *symbols)
{
	switch (expression->type)
	{
		// case EXPRESSION_ASSIGNMENT:
		// 	return TypeContext(VOID_INDEX);

		// case EXPRESSION_BOOLEAN_OR:
		// case EXPRESSION_BOOLEAN_AND:
		// case EXPRESSION_EQUALITY:
		// case EXPRESSION_RELATIONAL:
		// 	return TypeContext(BOOL_INDEX);

		// Infer type from args
		// case Conditional:
		// 	break;

		// Infer integer type from args
		// case BitwiseOr:
		// case BitwiseXor:
		// case BitwiseAnd:
		// case Shift:
		// 	break;
		
		// Infer type from args
		// case Additive:
		// case Multiplicative:
		// case Postfix:
		// case Prefix:
		// case Primary:
		// 	break;

		// case EXPRESSION_CONSTANT:
		// 	return getConstantType(&expression->constant);
		
		default:
			exitWithError("Invalid expression type: %d.", expression->type);
	}
}

static bool validateExpressionConversion(TypeContext *out, SymbolTable *symbols, const ExpressionContext *from, const TypeContext *to)
{
	exitNotImplemented();
	// switch (from->type)
	// {
		// case Assignment:
			
		// 	break;

		// case Conditional:
		// 	break;
		// case BooleanOr:
		// 	break;
		// case BooleanAnd:
		// 	break;
		// case BitwiseOr:
		// 	break;
		// case BitwiseXor:
		// 	break;
		// case BitwiseAnd:
		// 	break;
		// case Equality:
		// 	break;
		// case Relational:
		// 	break;
		// case Shift:
		// 	break;
		// case Additive:
		// 	break;
		// case Multiplicative:
		// 	break;
		// case Postfix:
		// 	break;
		// case Prefix:
		// 	break;
		// case Primary:
		// 	break;
		// case EXPRESSION_CONSTANT:
		// 	exitNotImplemented();
		// 	break;
			// if (!validateConversion(to, , symbols))
			// 	return false;
			// break;
		// }

		// case Symbol:
		// 	break;
	// 	default:
	// 		break;
	// }

	// throw std::invalidArgument("Invalid expression type %d.", from->type);
}

bool validateVariable(usize *out, const VariableSyntax *syntax, const ExpressionContext *value, SymbolTable *symbols)
{
	bool success = true;

	VariableContext context =
	{
		.name = tokenGetText(&syntax->name),
		.isExplicitlyTyped = syntax->isExplicitlyTyped,
		.isMutable = syntax->isMutable
	};

	if (syntax->isExplicitlyTyped)
	{
		success = success && validateType(&context.type, &syntax->type, symbols);
	}
	else
	{
		context.type = getExpressionType(value, symbols);
	}

	usize index = symbolTableAddVariable(symbols, &context);

	success = success && index != SIZE_MAX;

	if (!success)
		goto error;

	*out = index;

	return true;

error:

	freeVariableContext(&context);
	return false;
}

bool validateDeclarationStatement(DeclarationContext *out, const DeclarationSyntax *syntax, SymbolTable *symbols)
{
	DeclarationContext context = { 0 };
	
	if (!validateExpression(&context.value, &syntax->value, symbols))
		goto error;

	if (!validateVariable(&context.variableIndex, &syntax->variable, &context.value, symbols))
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
		
		if (!validateDeclarationStatement(&declaration, syntax->declaration, symbols))
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

bool validateFunction(const FunctionSyntax *syntax, SymbolTable *symbols)
{
	bool success = true;
	FunctionContext context = { 0 };
	char *name = tokenGetText(&syntax->name);
	SymbolData *data = symbolTableFindGlobal(symbols, name);

	success = success && data;

	if (!validateFunctionSignature(&context.signature, &syntax->signature, symbols))
		success = false;

	if (!validateExpression(&context.body, &syntax->body, symbols))
		success = false;

	if (!success)
		goto error;

	usize index = symbolTableAddFunction(symbols, &context);

	if (index == SIZE_MAX)
		goto error;

	return true;

error:

	freeFunctionContext(&context);
	return false;
}

bool validatePackage(const PackageSyntax *syntax, SymbolTable *symbols)
{
	bool success = true;
	PackageContext context =
	{
		.name = duplicateString(syntax->name)
	};

	for (usize i = 0; i < syntax->functionCount; ++i)
		success = success && validateFunction(syntax->functions + i, symbols);

	if (!success)
		goto error;

	ProgramContext *program = symbols->context;
	usize index = program->packageCount;

	resizeArray(program->packages, ++program->packageCount);

	program->packages[index] = context;

	return true;

error:

	freePackageContext(&context);
	return false;
}

bool validate(ProgramContext *out, const ProgramSyntax *syntax)
{
	bool success = true;

	ProgramContext context = { 0 };
	Scope scope = { 0 };
	SymbolTable symbols = symbolTableCreate(&context, syntax);

	for (usize i = 0; i < syntax->packageCount; ++i)
		success = success && validatePackage(syntax->packages + i, &symbols);

	scopeDestroy(&scope);

	if (!success)
		goto error;

	*out = context;
	return true;

error:

	freeProgramContext(&context);
	return false;
}
