#include <warbler/validator.h>
#include <warbler/util/print.h>

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
	char *name = getTokenText(&syntax->name);
	SymbolData *symbol = symbolTableFind(symbolTable, name);

	if (!symbol)
	{
		printTokenError(&syntax->name, "The type '%s' does not exist this scope.", name);
		return false;
	}

	if (isSymbolInvalid(symbol))
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

bool validateStructMember(MemberContext *out, const MemberSyntax *syntax, SymbolTable *symbols, ContainingTypes *containingTypes)
{
	MemberContext context =
	{
		.name = getTokenText(&syntax->name),
		.isPublic = syntax->isPublic
	};

	char *typeName = getTokenText(&syntax->type.name);
	SymbolData *symbol = symbolTableFindGlobal(symbols, typeName);

	if (symbol && symbol->type == SYMBOL_STRUCT && isSymbolNotYetValidated(symbol))
	{
		StructContext strct;

		if (!validateStruct(&strct, symbol->structSyntax, symbols, containingTypes))
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

bool validateStruct(StructContext *out, const StructSyntax *syntax, SymbolTable *symbols, ContainingTypes *containingTypes)
{
	char *identifier = getTokenText(&syntax->name);
	SymbolData *data = symbolTableFindGlobal(symbols, identifier);
	bool success = true;

	// FIXME: Push to pointer
	// containingTypes.pushBack(symbol);

	MemberContext *members;
	usize memberCount = 0;

	makeArray(members, syntax->memberCount);

	for (usize i = 0; i < syntax->memberCount; ++i)
	{
		MemberSyntax *memberSyntax = syntax->members + i;
		MemberContext context;

		success = success && validateStructMember(&context, memberSyntax, symbols, containingTypes);

		members[memberCount++] = context;

		if (!success)
		{
			char *name = getTokenText(&memberSyntax->name);

			printTokenError(&syntax->name, "A member with name '%s' is already declared in struct '%s'.", name, data->symbol);
			deallocate(name);
			// TODO: Show previous declaration
		}
	}

	// FIXME: Pop pointer
	// containingTypes.popBack();

	if (success)
	{
		char *symbol = duplicateString(data->symbol);

		StructContext context =
		{
			.symbol = symbol,
			.members = members,
			.memberCount = memberCount
		};
		
		symbolTableValidateStruct(symbols, data, &context);
	}
	else
	{
		for (usize i = 0; i < memberCount; ++i)
			freeMemberContext(members + i);

		deallocate(members);

		symbolDataInvalidate(data);
	}

	return success;
}

bool validateParameter(ParameterContext *out, const ParameterSyntax *syntax, SymbolTable *symbols)
{
	TypeContext context;

	if (!validateType(&context, &syntax->type, symbols))
		return false;

	char *name = getTokenText(&syntax->name);
	ParameterContext parameter =
	{
		.name = name,
		.type = context,
		.isMutable = syntax->isMutable
	};

	*out = parameter;

	return true;
}

bool validateParameterList(ParameterListContext *out, const ParameterListSyntax *syntax, SymbolTable *symbols)
{
	ParameterListContext parameters;
	
	parameters.count = syntax->count;

	makeArray(parameters.data, parameters.count);

	bool success = true;

	for (usize i = 0; i < syntax->count; ++i)
	{
		const ParameterSyntax *parameter = syntax->data + i;
		AddSymbolResult add = symbolTableAddParameter(symbols, parameter);

		success = success && add.success;

		ParameterContext context;

		success = success && validateParameter(&context, parameter, symbols);

		if (!success)
			continue;

		symbolTableValidateParameter(symbols, add.data, &context);

		parameters.data[i] = add.data->index;
	}

	if (!success)
		deallocate(parameters.data);

	return success;
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
	char *symbol = getTokenText(&syntax->token);
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

bool validateExpression(ExpressionContext *out, const ExpressionSyntax *syntax, SymbolTable *symbols)
{
	switch (syntax->type)
	{
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

// void printInvalidConversionError(const char *left, const char *right)
// {
// 	printError("Expected value of type '%s', but got '%s'.", left, right);
// }

// void printInvalidConversionError(const TypeContext *to, const TypeContext *from, const SymbolTable *globals)
// {
// 	char *toSymbol = symbolTableGetSymbol(to->type, to->index);
// 	char *fromSymbol = symbolTableGetSymbol(from->type, from->index);

// 	printInvalidConversionError(toSymbol, fromSymbol);
// }


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
	AddSymbolResult addResult = symbolTableAddVariable(symbols, syntax);
	SymbolData *data = addResult.data;
	bool success = addResult.success;

	VariableContext context =
	{
		.name = getTokenText(&syntax->name),
		.isExplicitlyTyped = syntax->isExplicitlyTyped,
		.isMutable = syntax->isMutable
	};

	if (syntax->isExplicitlyTyped)
	{
		if (!validateType(&context.type, &syntax->type, symbols))
			success = false;
	}
	else
	{
		context.type = getExpressionType(value, symbols);
	}

	if (success)
	{
		symbolTableValidateVariable(symbols, data, &context);
		*out = data->index;
	}
	else
	{
		freeVariableContext(&context);
		symbolDataInvalidate(data);
	}

	return success;
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

bool validateBlockStatement(BlockStatementContext *out, const BlockStatementSyntax *syntax, SymbolTable *symbols)
{
	BlockStatementContext context = { 0 };
	bool success = true;

	for (usize i = 0; i < syntax->count; ++i)
	{
		const StatementSyntax *statementSyntax = syntax->statements + i;

		StatementContext statement;

		if (!validateStatement(&statement, statementSyntax, symbols))
		{
			success = false;
			continue;
		}

		usize index = context.count;

		resizeArray(context.statements, ++context.count)[index] = statement; 
	}

	if (!success)
	{
		freeBlockStatementContext(&context);
		return false;
	}

	*out = context;

	return true;
}

bool validateStatement(StatementContext *out, const StatementSyntax *syntax, SymbolTable *symbols)
{
	switch (syntax->type)
	{
		case STATEMENT_DECLARATION:
			DeclarationContext declaration;
			
			if (!validateDeclarationStatement(&declaration, syntax->declaration, symbols))
				return false;

			*makeNew(out->declaration) = declaration;
			break;

		case STATEMENT_EXPRESSION:
			ExpressionContext expression;

			if (!validateExpressionStatement(&expression, syntax->expression, symbols))
				return false;

			*makeNew(out->expression) = expression;
			break;

		case STATEMENT_BLOCK:
			BlockStatementContext block;

			if (!validateBlockStatement(&block, syntax->block, symbols))
				return false;

			*makeNew(out->block) = block;
			break;

		default:
			exitWithError("Invalid StatementType: %d", syntax->type);
	}

	out->type = syntax->type;

	return true;
}

bool validateFunction(FunctionContext *out, const FunctionSyntax *syntax, SymbolTable *symbols)
{
	FunctionContext context = { 0 };
	
	bool success = true;

	char *name = getTokenText(&syntax->name);
	AddSymbolResult result = symbolTableAddFunction(symbols, syntax);

	success = success && result.success;

	FunctionSignatureContext signature;

	if (!validateFunctionSignature(&signature, &syntax->signature, symbols))
		success = false;

	BlockStatementContext body;

	if (!validateBlockStatement(&body, &syntax->body, symbols))
		success = false;

	if (!success)
	{
		freeFunctionContext(&context);
		return false;
	}

	symbolTableValidateFunction(symbols, result.data, &context);

	*out = context;

	return true;
}

bool validate(ProgramContext *out, const ProgramSyntax *syntax)
{
	ProgramContext context = { 0 };

	SymbolTable symbols;

	if (!symbolTableFromProgramSyntax(&symbols, syntax))
		return false;

	bool success = true;

	ContainingTypes containingTypes = { 0 };

	for (usize i = 0; i < symbols.globalSymbolCount; ++i)
	{
		const SymbolData *global = symbols.globalSymbols + i;

		if (isSymbolValidated(global))
			continue;

		symbolTableSetPackagesFromSymbol(&symbols, global->symbol);

		switch (global->type)
		{
			case SYMBOL_STRUCT:
				StructContext strct;
				success = success && validateStruct(&strct, global->structSyntax, &symbols, &containingTypes);
				containingTypes.count = 0;
				break;

			case SYMBOL_FUNCTION:
				FunctionContext function;
				success = success && validateFunction(&function, global->functionSyntax, &symbols);
				break;

			default:
				break;
		}
	}		

	if (!success)
		return false;

	*out = context;

	return true;
}
