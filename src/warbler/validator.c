#include <warbler/ast.h>
#include <warbler/symbol_id.h>
#include <warbler/type.h>
#include <warbler/validator.h>
#include <warbler/util/print.h>
#include <warbler/scope.h>
#include <string.h>

bool validateStruct(SymbolData *data);

SymbolId getLiteralSymbolId(Literal *literal)
{
	switch (literal->type)
	{
		case LITERAL_CHARACTER:
			return charSymbolId;

		case LITERAL_STRING:
			return stringSymbolId;

		case LITERAL_INTEGER:
			return i32SymbolId;

		case LITERAL_FLOAT:
			return f64SymbolId;

		case LITERAL_BOOLEAN:
			return boolSymbolId;

		default:
			break;
	}

	exitWithErrorFmt("Unable to get SymbolId for Literal of type: %d", literal->type);
}

Type getLiteralType(Literal *literal)
{
	Type type =
	{
		.id = getLiteralSymbolId(literal)
	};

	return type;
}

Type getExpressionType(Expression *expression)
{
	switch (expression->type)
	{
		case EXPRESSION_BLOCK:
			break;
		case EXPRESSION_ASSIGNMENT:
			break;
		case EXPRESSION_CONDITIONAL:
			break;
		case EXPRESSION_BOOLEAN_OR:
			break;
		case EXPRESSION_BOOLEAN_AND:
			break;
		case EXPRESSION_BITWISE_OR:
			break;
		case EXPRESSION_BITWISE_XOR:
			break;
		case EXPRESSION_BITWISE_AND:
			break;
		case EXPRESSION_EQUALITY:
			break;
		case EXPRESSION_RELATIONAL:
			break;
		case EXPRESSION_SHIFT:
			break;
		case EXPRESSION_ADDITIVE:
			break;
		case EXPRESSION_MULTIPLICATIVE:
			break;
		case EXPRESSION_POSTFIX:
			break;
		case EXPRESSION_PREFIX:
			break;
		case EXPRESSION_LITERAL:
			return getLiteralType(expression->literal);
		case EXPRESSION_SYMBOL:
			break;
	}

	exitWithErrorFmt("Unable to get type for expression of type: %d", expression->type);
}

bool validateType(Type *node, const Token *token)
{
	SymbolData *data = symbolTableResolve(token);

	if (!data)
		return false;
	
	node->id = data->id;

	switch (node->id.type)
	{
		case SYMBOL_STRUCT:
		case SYMBOL_PRIMITIVE:
			return true;

		default:
			break;
	}

	const char *typeName = symbolTypeGetName(node->id.type);

	printTokenError(token, "Expected type name, found %s.", typeName);

	return false;
}

bool canConvertType(Type *to, Type *from)
{
	const SymbolId *toId = &to->id;
	const SymbolId *fromId = &from->id;

	bool success = symbolIdEquals(toId, fromId);

	return success;
}

bool validateTypeAnnotation(TypeAnnotation *node)
{
	return validateType(&node->type, &node->token);
}

bool validateMemberList(MemberList *node)
{
	bool success = true;

	for (usize i = 0; i < node->count; ++i)
	{
		Member *member = &node->data[i];

		for (usize j = 0; j < i; ++j)
		{
			const Member *previous = &node->data[j];

			if (tokenEquals(&member->name, &previous->name))
			{
				success = false;
				
				printTokenError(&member->name, "A member with same name is already declared in this struct.");
				printTokenNote(&previous->name, "Previous delcaration here.");

				break;
			}
		}

		if (!validateTypeAnnotation(&member->annotation))
			success = false;
			// printTokenError(&member->name, "Declaration of member causes infinite recursion in struct '%s'.", node->symbol);
	}

	return success;
}

bool validateStruct(SymbolData *data)
{
	bool success = true;

	Struct *node = symbolTableGetStruct(&data->id);

	if (!validateMemberList(&node->members))
		success = false;

	data->status = success
		? VALIDATION_VALID
		: VALIDATION_INVALID;

	return success;
}

bool validateLiteral(Literal *node)
{
	assert(node);

	return true;
}

bool validateSymbol(Symbol *node)
{
	assert(node);
	const SymbolData *data = symbolTableResolve(&node->token);

	if (!data)
		return false;
	
	node->id = data->id;

	return data->status == VALIDATION_VALID;
}

bool validateAssignment(Assignment *node)
{
	bool success = true;

	if (!validateExpression(&node->lhs))
		success = false;

	if (!validateExpression(&node->rhs))
		success = false;

	// TODO: validate type of assignment

	return success;
}

bool validateBlock(Block *node)
{
	bool success = true;

	for (usize i = 0; i < node->count; ++i)
	{
		if (!validateStatement(&node->statements[i]))
			success = false;
	}

	printFmt("Block success: %d", success);

	return success;
}

bool validatePrefix(Prefix *node)
{
	assert(node);
	exitNotImplemented();
}

bool validateArgumentList(ArgumentList *node)
{
	assert(node);
	exitNotImplemented();
}

bool validatePostfix(Postfix *node)
{
	if (!validateExpression(&node->expression))
		return false;
	
	switch (node->type)
	{
		case POSTFIX_INDEX:
			exitWithError("Postfix indexing not implemented");
			break;

		case POSTFIX_FUNCTION_CALL:
			exitWithError("Postfix function call not implemented");
			break;

		case POSTFIX_MEMBER:
			exitWithError("Postfix member validation not implemented");
			break;
	}

	return true;
}

bool validateMultiplicativeExpression(MultiplicativeExpression *node)
{
	bool success = true;

	if (!validateExpression(&node->lhs))
		success = false;

	for (usize i = 0; i < node->rhsCount; ++i)
	{
		if (!validateExpression(&node->rhs[i].expr))
			success = false;
	}

	return success;
}

bool validateAdditiveExpression(AdditiveExpression *node)
{
	bool success = true;

	if (!validateExpression(&node->lhs))
		success = false;

	for (usize i = 0; i < node->rhsCount; ++i)
	{
		if (!validateExpression(&node->rhs[i].expr))
			success = false;
	}

	return success;
}

bool validateExpression(Expression *node)
{
	switch (node->type)
	{
		case EXPRESSION_BLOCK:
			return validateBlock(node->block);

		case EXPRESSION_ASSIGNMENT:
			return validateAssignment(node->assignment);

		case EXPRESSION_CONDITIONAL:
			// evaluate types of both branch, confirm are the same and return that
			break;

		case EXPRESSION_BOOLEAN_OR:
			break;

		case EXPRESSION_BOOLEAN_AND:
			break;

		case EXPRESSION_BITWISE_OR:
			break;

		case EXPRESSION_BITWISE_XOR:
			break;

		case EXPRESSION_BITWISE_AND:
			break;

		case EXPRESSION_EQUALITY:
			break;

		case EXPRESSION_RELATIONAL:
			break;

		case EXPRESSION_SHIFT:
			break;

		case EXPRESSION_ADDITIVE:
			return validateAdditiveExpression(node->additive);

		case EXPRESSION_MULTIPLICATIVE:
			return validateMultiplicativeExpression(node->multiplicative);

		case EXPRESSION_POSTFIX:
			return validatePostfix(node->postfix);

		case EXPRESSION_PREFIX:
			return validatePrefix(node->prefix);
		
		case EXPRESSION_LITERAL:
			return validateLiteral(node->literal);

		case EXPRESSION_SYMBOL:
			return validateSymbol(&node->symbol);

		default:
			break;
	}

	exitWithErrorFmt("Invalid expression type: %d.", node->type);
}

bool validateVariable(const SymbolId *id)
{
	if (!symbolTableDeclareLocal(id))
		return false;
	
	Local *node = symbolTableGetVariable(id);

	if (node->isExplicitlyTyped)
		return validateTypeAnnotation(&node->type);

	return true;
}

bool validateDeclaration(Declaration *node)
{
	bool success = true;

	if (!validateVariable(&node->variableId))
		success = false;

	if (!validateExpression(&node->value))
		success = false;
	
	if (!success)
		return false;

	Local *variable = symbolTableGetVariable(&node->variableId);
	Type expressionType = getExpressionType(&node->value);

	if (variable->isExplicitlyTyped)
	{
		Type *variableType = &variable->type.type;

		if (!canConvertType(variableType, &expressionType))
		{
			const char *toSymbol = symbolTableGetSymbol(&variableType->id);
			const char *fromSymbol = symbolTableGetSymbol(&expressionType.id);

			// TODO: Make error highlight entire statement
			printTokenError(&variable->name, "Variable of type `%s` cannot be initialized with value of type `%s`.", toSymbol, fromSymbol);

			return false;
		}
	}
	else
	{
		variable->type.type = expressionType;
	}

	return true;
}

bool validateStatement(Statement *node)
{
	if (node->isDeclaration)
		return validateDeclaration(node->declaration);
	
	return validateExpression(node->expression);
}

bool validateParameter(const SymbolId *id)
{	
	Local *node = symbolTableGetParameter(id);

	if (!validateTypeAnnotation(&node->type))
		return false;

	return true;
}

bool validateParameterList(SymbolIdList *ids)
{
	bool success = true;

	for (usize i = 0; i < ids->count; ++i)
	{
		SymbolId id = { ids->type, ids->indeces[i] };

		if (!symbolTableDeclareLocal(&id))
			success = false;

		if (!validateParameter(&id))
			success = false;
	}

	return success;
}

bool validateFunction(SymbolData *data)
{
	bool success = true;
	printFmt("Validate function: %s", data->symbol);
	Function *node = symbolTableGetFunction(&data->id);

	// TODO: Add function symbols

	if (!validateParameterList(&node->parameterIds))
		success = false;

	if (node->hasReturnType && !validateTypeAnnotation(&node->returnType))
		success = false;

	if (!validateExpression(&node->body))
		success = false;

	printFmt("Function Success: %d", success);

	data->status = success
		? VALIDATION_VALID
		: VALIDATION_INVALID;

	return success;
}

bool declareModule(const Module *module)
{
	bool success = true;

	if (!symbolIdListForEach(&module->structIds, symbolTableDeclareGlobal))
		success = false;

	if (!symbolIdListForEach(&module->functionIds, symbolTableDeclareGlobal))
		success = false;

	return success;
}

bool declarePackage(const SymbolId *id)
{
	bool success = symbolTableDeclareGlobal(id);

	Package *package = symbolTableGetPackage(id);

	for (usize i = 0; i < package->moduleCount; ++i)
	{
		if (!declareModule(&package->modules[i]))
			success = false;
	}

	return success;
}

bool validateGlobal(SymbolData *data)
{
	if (data->status != VALIDATION_PENDING)
		return data->status == VALIDATION_VALID;
		
	switch (data->id.type)
	{
		case SYMBOL_FUNCTION:
			return validateFunction(data);

		case SYMBOL_STRUCT:
			return validateStruct(data);

		default:
			break;
	}

	return true;
}

static const MemberList *getGlobalMembers(const SymbolId *id)
{
	switch (id->type)
	{
		case SYMBOL_STRUCT:
		{
			const Struct *node = symbolTableGetStruct(id);

			return &node->members;
		}

		default:
			break;
	}

	return NULL;
}

static const Member *getRecursiveMember(const MemberList *members, const char *symbol)
{
	for (usize i = 0; i < members->count; ++i)
	{
		const Member *member = &members->data[i];
		const Type *memberType = &member->annotation.type;
		const SymbolId *memberTypeId = &memberType->id;
		const char *memberTypeSymbol = symbolTableGetSymbol(memberTypeId);
		// TODO: Indirection check

		if (!strcmp(memberTypeSymbol, symbol))
			return member;

		const MemberList *memberTypeMembers = getGlobalMembers(memberTypeId);

		if (!memberTypeMembers)
			continue;

		if (getRecursiveMember(memberTypeMembers, symbol))
			return member;
	}
	
	return NULL;
}

bool validateTypeRecursion(const SymbolId *id)
{
	const MemberList *members = getGlobalMembers(id);

	if (!members)
		return true;

	const char *symbol = symbolTableGetSymbol(id);
	const Member *recursiveMember = getRecursiveMember(members, symbol);

	if (recursiveMember)
	{
		printTokenError(&recursiveMember->name, "Declaration of member creates recursive type");
		return false;
	}

	return true;
}

bool validate()
{
	bool success = true;

	if (!symbolTableForEachEntity(SYMBOL_PACKAGE, declarePackage))
		success = false;

	if (!symbolTableForEachGlobal(validateGlobal))
		success = false;

	if (!symbolTableForEachEntity(SYMBOL_STRUCT, validateTypeRecursion))
		success = false;

	if (!success)
		symbolTableDestroy();

	return success;
}
