#include <warbler/validator.h>
#include <warbler/util/print.h>
#include <warbler/conversion.h>
#include <warbler/scope.h>
#include <string.h>

bool validateType(TypeAnnotation *node)
{
	// TODO: Optimize name
	SymbolId *id = symbolTableResolve(&node->token);

	if (!id)
		return false;

	node->type.id = *id;

	switch (id->type)
	{
		case SYMBOL_PACKAGE:
		case SYMBOL_PRIMITIVE:
			break;

		default:
		{
			const char *typeName = symbolTypeGetName(id->type);
			printTokenError(&node->token, "Expected type name, found %s.", typeName);
			return false;
		}
	}

	return true;
}

bool validateStructMember(Member *node)
{
	return validateType(&node->type);
}

bool validateStructDeclaration(const SymbolId *id)
{
	return symbolTableDeclareGlobal(id);
}

static bool isRecursiveType(const char *symbol, const Struct *node)
{
	printFmt("TODO: Implement %s", __func__);
	// exitNotImplemented();
	// TODO: Implement this
	// for (usize i = 0; i < node->memberCount; ++i)
	// {
	// 	const Member *member = &node->members[i];
	// 	char *identifier = tokenGetText(&member->name);
	// 	SymbolId *typeId = symbolTableResolve(identifier);

	// 	deallocate(identifier);

	// 	if (typeIf->type != SYMBOL_STRUCT)
	// 		continue;

	// 	const Str
	// }

	return false;
}

bool validateStructDefinition(const SymbolId *id)
{
	bool success = true;

	// TODO: Validate recursive types

	Struct *node = symbolTableGetStruct(id);

	if (isRecursiveType(node->symbol, node))
		success = false;

	for (usize i = 0; i < node->memberCount; ++i)
	{
		const Member *member = &node->members[i];

		for (usize j = 0; j < i; ++j)
		{
			const Member *previous = &node->members[j];

			if (tokenIsSame(&member->name, &previous->name))
			{
				success = false;
				// TODO: Stack based string
				char *name = tokenGetText(&member->name);

				printTokenError(&member->name, "A member with name '%s' is already declared in struct '%s'.", name, node->symbol);
				printTokenNote(&previous->name, "Previous delcaration here.");
				deallocate(name);
				break;
			}
		}

		if (!validateStructMember(&node->members[i]))
			success = false;
	}

	return success;
}

bool validateLiteral(Literal *node)
{
	return true;
}

bool validateSymbol(Symbol *node)
{
	SymbolId *id = symbolTableResolve(&node->token);

	if (!id)
		return false;
	
	node->id = *id;

	return true;
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

	return success;
}

bool validatePrefix(Prefix *node)
{
	exitNotImplemented();
}

bool validateArgumentList(ArgumentList *node)
{
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
	
	Variable *node = symbolTableGetVariable(id);

	if (node->isExplicitlyTyped)
		return validateType(&node->type);

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

	// TODO: Validate expression types
	// Variable *variable = symbolTableGetVariable(&node->variableId);
	// if (!variable->isExplicityTyped)
	// 	variable->type = getExpressionType(&node->value);

	return true;
}

bool validateStatement(Statement *node)
{
	if (node->isDeclaration)
	{		
		if (!validateDeclaration(node->declaration))
			return false;
	}
	else
	{
		if (!validateExpression(node->expression))
			return false;
	}

	return true;
}

bool validateParameter(SymbolId *id)
{	
	Parameter *node = symbolTableGetParameter(id);

	if (!validateType(&node->type))
		return false;

	return true;
}

bool validateParameterList(SymbolIdList *ids)
{
	bool success = true;

	for (usize i = 0; i < ids->count; ++i)
	{
		SymbolId id = { ids->type, ids->indeces[i] };

		if (!validateParameter(&id))
			success = false;
	}

	return success;
}

bool validateFunctionDeclaration(SymbolId *id)
{
	bool success = true;
	Function *node = symbolTableGetFunction(id);

	if (!symbolTableDeclareGlobal(id))
		success = false;

	if (!validateParameterList(&node->parameterIds))
		success = false;

	if (node->hasReturnType)
	{
		if (!validateType(&node->returnType))
			success = false;
	}

	return success;
}

bool validateFunctionDefinition(const SymbolId *id)
{
	Function *node = symbolTableGetFunction(id);

	return validateExpression(&node->body);
}

static bool validateModuleDeclarations(Module *node)
{
	bool success = true;

	for (usize i = 0; i < node->functionIds.count; ++i)
	{
		SymbolId id = { node->functionIds.type, node->functionIds.indeces[i] };

		if (!validateFunctionDeclaration(&id))
			success = false;
	}

	for (usize i = 0; i < node->structIds.count; ++i)
	{
		SymbolId id = { node->structIds.type, node->structIds.indeces[i] };

		if (!validateStructDeclaration(&id))
			success = false;
	}

	return success;
}

static bool validateModuleDefinitions(const Module *node)
{
	bool success = true;

	for (usize i = 0; i < node->functionIds.count; ++i)
	{
		SymbolId id = { node->functionIds.type, node->functionIds.indeces[i] };

		if (!validateFunctionDefinition(&id))
			success = false;
	}

	for (usize i = 0; i < node->structIds.count; ++i)
	{
		SymbolId id = { node->structIds.type, node->structIds.indeces[i] };

		if (!validateStructDefinition(&id))
			success = false;
	}

	return success;
}

static bool validatePackageDeclarations(const Package *node)
{
	printFmt("packagedeclarations: %s", node->symbol);
	bool success = true;

	for (usize i = 0; i < node->moduleCount; ++i)
	{
		if (!validateModuleDeclarations(&node->modules[i]))
			success = false;
	}

	return success;
}

static bool validatePackageDefinitions(const Package *node)
{
	bool success = true;

	for (usize i = 0; i < node->moduleCount; ++i)
	{
		if (!validateModuleDefinitions(&node->modules[i]))
			success = false;
	}

	return success;
}

bool validate()
{
	bool success = true;

	usize packageCount = symbolTablePackageCount();

	for (usize i = 0; i < packageCount; ++i)
	{
		SymbolId packageId = { SYMBOL_PACKAGE, i };
		Package *package = symbolTableGetPackage(&packageId);

		if (!validatePackageDeclarations(package))
			success = false;
	}

	for (usize i = 0; i < packageCount; ++i)
	{
		SymbolId packageId = { SYMBOL_PACKAGE, i };
		Package *package = symbolTableGetPackage(&packageId);

		if (!validatePackageDefinitions(package))
			success = false;
	}

	// TODO: Validate

	// for (usize i = 0; i < count; ++i)
	// {
	// 	const Validation *validation = symbolTableValidationAt(i);

	// 	switch (validation->id.type)
	// 	{
	// 		case SYMBOL_STRUCT:
	// 			validateStructDefinition(&validation->id, validation->struct);
	// 			break;

	// 		case SYMBOL_FUNCTION:
	// 			validateFunctionDefinition(&validation->id, validation->function);
	// 			break;

	// 		default:
	// 			exitWithErrorFmt("Invalid validation symbol type: %d", validation->id.type);
	// 	}
	// }

	if (!success)
		symbolTableDestroy();

	return success;
}
