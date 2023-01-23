#include "warbler/ast.h"
#include "warbler/context.h"
#include "warbler/scope.h"
#include "warbler/symbol_id.h"
#include "warbler/symbol_table.h"
#include "warbler/type.h"
#include "warbler/util/memory.h"
#include "warbler/util/print.h"
#include "warbler/validator.h"

#include <string.h>

bool validateTypeAnnotation(TypeAnnotation *node, const Scope *packageScope)
{
	assert(node != NULL);
	assert(packageScope != NULL);

	const Token *token = &node->token;
	Symbol *symbol = symbolTableResolveGlobal(packageScope, token);

	if (!symbol)
		return false;

	switch (symbol->type)
	{
		case SYMBOL_STRUCT:
		case SYMBOL_PRIMITIVE:
			node->type = (Type)
			{
				.type = symbol->type,
				.index = symbol->index
			};

			return true;

		default:
			break;
	}

	const char *typeName = symbolTypeGetName(symbol->type);

	printTokenError(token, "Expected type name, found %s.", typeName);

	return false;
}

bool validateMemberList(MemberList *node, const Scope *packageScope)
{
	assert(node != NULL);
	assert(packageScope != NULL);

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

		if (!validateTypeAnnotation(&member->annotation, packageScope))
			success = false;
			// printTokenError(&member->name, "Declaration of member causes infinite recursion in struct '%s'.", node->symbol);
	}

	return success;
}

bool validateStruct(Struct *node, const Scope *packageScope)
{
	bool success = true;

	if (!validateMemberList(&node->members, packageScope))
		success = false;

	return success;
}

bool validateLiteral(Literal *node)
{
	assert(node != NULL);

	return true;
}

bool validateIdentifier(Identifier *node, LocalSymbolTable *localTable)
{
	assert(node != NULL);
	assert(localTable != NULL);

	const Symbol *symbol = symbolTableResolve(localTable, &node->token);

	if (!symbol)
		return false;

	switch (symbol->type)
	{
		case SYMBOL_PACKAGE:
		case SYMBOL_STRUCT:
			printTokenError
			(
				&node->token,
				"Expected identifier, found %s `%s`.",
				symbolTypeName(symbol->type),
				symbol->key
			);
			return false;

		default:
			break;
	}
	
	node->index = symbol->index;
	node->type = symbol->type;

	return true;
}

bool validateAssignment(Assignment *node, LocalSymbolTable *localTable)
{
	assert(node != NULL);
	assert(localTable != NULL);

	bool success = true;

	if (!validateExpression(&node->lhs, localTable))
		success = false;

	if (!validateExpression(&node->rhs, localTable))
		success = false;

	// TODO: validate type of assignment

	return success;
}

bool validateBlock(Block *node, LocalSymbolTable *localTable)
{
	assert(node != NULL);
	assert(localTable != NULL);

	bool success = true;

	localSymbolTablePushBlock(localTable, node);

	for (usize i = 0; i < node->count; ++i)
	{
		if (!validateStatement(&node->statements[i], localTable))
			success = false;
	}

	localSymbolTablePopBlock(localTable);

	return success;
}

bool validatePrefix(Prefix *node, LocalSymbolTable *localTable)
{
	assert(node);
	exitNotImplemented();
}

bool validateArgumentList(ArgumentList *node)
{
	assert(node);
	exitNotImplemented();
}

bool validatePostfix(Postfix *node, LocalSymbolTable *localTable)
{
	if (!validateExpression(&node->expression, localTable))
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

bool validateMultiplicativeExpression(MultiplicativeExpression *node, LocalSymbolTable *localTable)
{
	bool success = true;

	if (!validateExpression(&node->lhs, localTable))
		success = false;

	for (usize i = 0; i < node->rhsCount; ++i)
	{
		if (!validateExpression(&node->rhs[i].expr, localTable))
			success = false;
	}

	return success;
}

bool validateAdditiveExpression(AdditiveExpression *node, LocalSymbolTable *localTable)
{
	bool success = true;

	if (!validateExpression(&node->lhs, localTable))
		success = false;

	for (usize i = 0; i < node->rhsCount; ++i)
	{
		if (!validateExpression(&node->rhs[i].expr, localTable))
			success = false;
	}

	return success;
}

bool validateExpression(Expression *node, LocalSymbolTable *localTable)
{
	switch (node->type)
	{
		case EXPRESSION_BLOCK:
			return validateBlock(node->block, localTable);

		case EXPRESSION_ASSIGNMENT:
			return validateAssignment(node->assignment, localTable);

		case EXPRESSION_CONDITIONAL:
			// evaluate types of both branch, confirm are the same and return that
			break;

		case EXPRESSION_BOOLEAN_OR:
			// confirm both types have bool operator
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
			return validateAdditiveExpression(node->additive, localTable);

		case EXPRESSION_MULTIPLICATIVE:
			return validateMultiplicativeExpression(node->multiplicative, localTable);

		case EXPRESSION_POSTFIX:
			return validatePostfix(node->postfix, localTable);

		case EXPRESSION_PREFIX:
			return validatePrefix(node->prefix, localTable);
		
		case EXPRESSION_LITERAL:
			return validateLiteral(node->literal);

		case EXPRESSION_IDENTIFIER:
			return validateIdentifier(&node->identifier, localTable);

		default:
			break;
	}

	exitWithErrorFmt("Unable to validate Expression with type: %d.", node->type);
}

bool validateVariable(Local *node, LocalSymbolTable *localTable)
{
	if (node->isExplicitlyTyped)
		return validateTypeAnnotation(&node->annotation, localTable->packageScope);

	return true;
}

bool validateDeclaration(Declaration *node, LocalSymbolTable *localTable)
{
	bool success = true;

	if (!symbolTableDeclareLocal(localTable, SYMBOL_VARIABLE, node->variableId))
		success = false;

	Local *variable = symbolTableGetVariable(node->variableId);
	
	if (!validateVariable(variable, localTable))
		success = false;

	if (!validateExpression(&node->value, localTable))
		success = false;
	
	if (!success)
		return false;

	Type *variableType = variable->isExplicitlyTyped
		? &variable->annotation.type
		: NULL;
	Type expressionType = typeFromExpression(&node->value, variableType);

	if (variable->isExplicitlyTyped)
	{
		Type *variableType = &variable->annotation.type;

		if (!typeCanConvert(variableType, &expressionType))
		{
			char *toTypeName = typeGetName(&expressionType);
			char *fromTypeName = typeGetName(variableType);

			// TODO: Make error highlight entire statement
			printTokenError(&variable->name, "Variable of type `%s` cannot be initialized with value of type `%s`.", toTypeName, fromTypeName);
			deallocate(toTypeName);
			deallocate(fromTypeName);

			return false;
		}
	}
	else
	{
		variable->annotation.type = expressionType;
	}

	return true;
}

bool validateReturnStatement(JumpStatement *node, LocalSymbolTable *localTable)
{
	if (node->hasValue && !validateExpression(&node->value, localTable))
		return false;

	Function *function = localTable->function;
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
		char *returnTypeName = typeGetName(returnType);

		printError("Return value is not compatible with return type `%s`.", returnTypeName);
		deallocate(returnTypeName);

		return false;
	}

	return true;
}

bool validateYieldStatement(JumpStatement *node, LocalSymbolTable *localTable)
{
	Block *currentBlock = localSymbolTableGetCurrentBlock(localTable);

	if (currentBlock == NULL)
	{
		printTokenError(&node->token, "Yield statement must be within a block.");

		return false;
	}

	const Type *blockReturnType = currentBlock->hasReturnType
		? &currentBlock->returnType
		: &voidType;
	// TODO: Confirm copying type is OK
	Type valueType = node->hasValue
		? typeFromExpression(&node->value, blockReturnType)
		: typeDuplicate(&voidType);

	if (typeCanConvert(blockReturnType, &valueType))
	{
		const char *blockTypeName = typeGetName(blockReturnType);
		// TODO: get type token

		printError("Yield value is not compatible with type of block expression `%s`.", blockTypeName);

		return false;
	}

	return true;
}

bool validateJumpStatement(JumpStatement *node, LocalSymbolTable *localTable)
{
	switch (node->type)
	{
		case JUMP_RETURN:
			return validateReturnStatement(node, localTable);

		case JUMP_BREAK:
			break;

		case JUMP_CONTINUE:
			break;

		case JUMP_YIELD:
			return validateYieldStatement(node, localTable);

		default:
			break;
	}
	
	exitWithErrorFmt("Unable to validate JumpStatement with type: %d", node->type);
}

bool validateStatement(Statement *node, LocalSymbolTable *localTable)
{
	switch (node->type)
	{
		case STATEMENT_EXPRESSION:
			return validateExpression(node->expression, localTable);

		case STATEMENT_DECLARATION:
			return validateDeclaration(node->declaration, localTable);

		case STATEMENT_JUMP:
			return validateJumpStatement(node->jump, localTable);

		default:
			break;
	}

	exitWithErrorFmt("Unable to validate Statement with StatementType: %d", node->type);
}

bool validateParameter(Local *node, LocalSymbolTable *localTable)
{	
	if (!validateTypeAnnotation(&node->annotation, localTable->packageScope))
		return false;

	return true;
}

bool validateParameterList(const IdList *ids, LocalSymbolTable *localTable)
{
	bool success = true;

	for (usize i = 0; i < ids->count; ++i)
	{
		usize index = idListGet(ids, i);

		if (!symbolTableDeclareLocal(localTable, SYMBOL_PARAMETER, index))
			success = false;

		Local *node = symbolTableGetParameter(index);

		if (!validateParameter(node, localTable))
			success = false;
	}

	return success;
}

bool validateFunction(Function *node, LocalSymbolTable *localTable)
{
	bool success = true;

	if (!validateParameterList(&node->parameterIds, localTable))
		success = false;

	if (node->hasReturnType
		&& !validateTypeAnnotation(&node->returnType, localTable->packageScope))
		success = false;

	if (!validateExpression(&node->body, localTable))
		success = false;

	if (success)
	{
		const Type *returnType = functionGetReturnType(node);
		Type bodyType = typeFromExpression(&node->body, returnType);

		if (!typeCanConvert(returnType, &bodyType))
		{
			char *returnTypeName = typeGetName(returnType);
			char *bodyTypeName = typeGetName(&bodyType);
			// TODO: handle token like so: Token token = tokenFromExpression(&node->body);

			printError("Expected `%s`, got `%s`.", returnTypeName, bodyTypeName);
			printTokenNote(&node->returnType.token, "Function return type here.");
			deallocate(returnTypeName);
			deallocate(bodyTypeName);

			success = false;
		}
	}	

	return success;
}

bool declareModule(const Module *module)
{
	bool success = true;
	const IdList *structIds = &module->structIds;
	const IdList *functionIds = &module->functionIds;

	for (usize i = 0; i < structIds->count; ++i)
	{
		usize index = idListGet(structIds, i);

		if (!symbolTableDeclareGlobal(SYMBOL_STRUCT, index))
			success = false;
	}

	for (usize i = 0; i < functionIds->count; ++i)
	{
		usize index = idListGet(functionIds, i);

		if (!symbolTableDeclareGlobal(SYMBOL_FUNCTION, index))
			success = false;
	}

	return success;
}

bool declarePackage(usize index)
{
	bool success = symbolTableDeclareGlobal(SYMBOL_PACKAGE, index);
	Package *package = symbolTableGetPackage(index);

	for (usize i = 0; i < package->moduleCount; ++i)
	{
		if (!declareModule(&package->modules[i]))
			success = false;
	}

	return success;
}

static const MemberList *getGlobalMembers(SymbolType type, usize index)
{
	switch (type)
	{
		case SYMBOL_STRUCT:
		{
			const Struct *node = symbolTableGetStruct(index);

			return &node->members;
		}

		default:
			break;
	}

	return NULL;
}

static const Member *getRecursiveMember(const MemberList *members, const char *key)
{
	for (usize i = 0; i < members->count; ++i)
	{
		const Member *member = &members->data[i];
		const Type *memberType = &member->annotation.type;
		const char *memberTypeKey = symbolGetKey(memberType->type, memberType->index);
		// TODO: Indirection check

		if (!strcmp(memberTypeKey, key))
			return member;

		const MemberList *memberTypeMembers = getGlobalMembers(memberType->type, memberType->index);

		if (!memberTypeMembers)
			continue;

		if (getRecursiveMember(memberTypeMembers, key))
			return member;
	}
	
	return NULL;
}

bool validateTypeRecursion(SymbolType type, usize index)
{
	const MemberList *members = getGlobalMembers(type, index);

	if (!members)
		return true;

	const char *key = symbolGetKey(type, index);
	const Member *recursiveMember = getRecursiveMember(members, key);

	if (recursiveMember)
	{
		printTokenError(&recursiveMember->name, "Declaration of member creates recursive type");
		return false;
	}

	return true;
}

bool validateStructRecursion(usize index)
{
	return validateTypeRecursion(SYMBOL_STRUCT, index);
}

bool validateModule(Module *module, const Scope *packageScope)
{
	assert(module != NULL);
	assert(packageScope != NULL);

	bool success = true;
	IdList *functionIds = &module->functionIds;
	IdList *structIds = &module->structIds;
	LocalSymbolTable localTable = localSymbolTableCreate(packageScope);

	for (usize i = 0; i < functionIds->count; ++i)
	{
		usize index = idListGet(functionIds, i);
		Function *function = symbolTableGetFunction(index);

		localTable.function = function;

		if (!validateFunction(function, &localTable))
			success = false;

		localSymbolTableClear(&localTable);
	}

	for (usize i = 0; i < structIds->count; ++i)
	{
		usize index = idListGet(structIds, i);
		Struct *node = symbolTableGetStruct(index);

		if (!validateStruct(node, packageScope))
			success = false;
	}

	return success;
}

bool validatePackage(usize index)
{
	bool success = true;
	Package *package = symbolTableGetPackage(index);
	Scope scope = scopeFromKey(package->symbol);

	for (usize i = 0; i < package->moduleCount; ++i)
	{
		if (!validateModule(&package->modules[i], &scope))
			success = false;
	}

	scopeDestroy(&scope);

	return success;
}

bool validate(void)
{
	bool success = true;

	if (!symbolTableForEachEntity(SYMBOL_PACKAGE, declarePackage))
		success = false;

	if (!symbolTableForEachEntity(SYMBOL_PACKAGE, validatePackage))
		success = false;

	if (!symbolTableForEachEntity(SYMBOL_STRUCT, validateStructRecursion))
		success = false;

	return success;
}
