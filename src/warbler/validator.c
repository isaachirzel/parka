#include <warbler/symbol_table.h>
#include <warbler/ast.h>
#include <warbler/symbol_id.h>
#include <warbler/type.h>
#include <warbler/validator.h>
#include <warbler/util/print.h>
#include <warbler/scope.h>
#include <string.h>

bool validateStruct(SymbolData *data);

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

	symbolTableSelectBlock(node);

	for (usize i = 0; i < node->count; ++i)
	{
		if (!validateStatement(&node->statements[i]))
			success = false;
	}

	symbolTableDeselectBlock();

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
	Type *variableType = variable->isExplicitlyTyped
		? &variable->type.type
		: NULL;
	Type expressionType = typeFromExpression(&node->value, variableType);

	if (variable->isExplicitlyTyped)
	{
		Type *variableType = &variable->type.type;

		if (!typeCanConvert(variableType, &expressionType))
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

bool validateReturnStatement(JumpStatement *node)
{
	Function *function = symbolTableGetSelectedFunction();
	const Type *returnType = functionGetReturnType(function);
	Type valueType = node->hasValue
		? typeFromExpression(&node->value, returnType)
		: typeDuplicate(&voidType);
	Expression *functionBody = &function->body;

	if (functionBody->type == EXPRESSION_BLOCK)
	{
		Block *block = functionBody->block;

		block->returnType = typeDuplicate(&valueType);
		block->hasReturnType = true;
	}

	if (!typeCanConvert(returnType, &valueType))
	{
		const char *returnTypeSymbol = symbolTableGetSymbol(&returnType->id);

		printError("Return value is not compatible with return type `%s`", returnTypeSymbol);

		return false;
	}

	return true;
}

bool validateYieldStatement(JumpStatement *node)
{
	Block *currentBlock = symbolTableGetSelectedBlock();
	const Type *blockReturnType = currentBlock->hasReturnType
		? &currentBlock->returnType
		: &voidType;
	// TODO: Confirm copying type is OK
	Type valueType = node->hasValue
		? typeFromExpression(&node->value, blockReturnType)
		: typeDuplicate(&voidType);

	if (typeCanConvert(blockReturnType, &valueType))
	{
		const char *blockTypeSymbol = symbolTableGetSymbol(&blockReturnType->id);

		printError("Yield value is not compatible with type of block expression `%s`", blockTypeSymbol);

		return false;
	}

	return true;
}

bool validateJumpStatement(JumpStatement *node)
{
	switch (node->type)
	{
		case JUMP_RETURN:
			return validateReturnStatement(node);

		case JUMP_BREAK:
			break;

		case JUMP_CONTINUE:
			break;

		case JUMP_YIELD:
			return validateYieldStatement(node);

		default:
			break;
	}
	
	exitWithErrorFmt("Unable to validate JumpStatement with type: %d", node->type);
}

bool validateStatement(Statement *node)
{
	switch (node->type)
	{
		case STATEMENT_EXPRESSION:
			return validateExpression(node->expression);

		case STATEMENT_DECLARATION:
			return validateDeclaration(node->declaration);

		case STATEMENT_JUMP:
			return validateJumpStatement(node->jump);

		default:
			break;
	}

	exitWithErrorFmt("Unable to validate Statement with StatementType: %d", node->type);
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
	printFmt("Validate function: %s", data->symbol);

	bool success = true;
	Function *node = symbolTableSelectFunction(&data->id);

	// TODO: Add function symbols

	if (!validateParameterList(&node->parameterIds))
		success = false;

	if (node->hasReturnType && !validateTypeAnnotation(&node->returnType))
		success = false;

	if (!validateExpression(&node->body))
		success = false;

	if (success)
	{
		const Type *returnType = functionGetReturnType(node);
		Type bodyType = typeFromExpression(&node->body, returnType);

		if (!typeCanConvert(returnType, &bodyType))
		{
			const char *symbol = symbolTableGetSymbol(&returnType->id);
			Token token = tokenFromExpression(&node->body);

			printTokenError(&token, "Expected `%s`, got .", symbol);

			success = false;
		}
	}

	data->status = success
		? VALIDATION_VALID
		: VALIDATION_INVALID;

	symbolTableDeselectFunction();

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

bool validate(void)
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
