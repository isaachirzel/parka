#include "warbler/ast/expression/expression.h"
#include "warbler/ast/statement/declaration.h"
#include "warbler/ast/variable.h"
#include "warbler/symbol_table.h"
#include "warbler/util/print.h"

bool parseDeclaration(Declaration *node, Token *token)
{
	usize index = symbolTableAddVariable();
	Variable *variable = symbolTableGetVariable(index);

	node->variableId = index;

	if (!parseVariable(variable, token))
		return false;

	if (token->type != TOKEN_ASSIGN)
	{
		printParseError(token, "expected '=' after declaration", NULL);
		return false;
	}

	incrementToken(token);

	if (!parseExpression(&node->value, token))
		return false;

	if (token->type != TOKEN_SEMICOLON)
	{
		printFmt("TOKEN: %zu, %s", token->length, tokenGetText(token));

		printParseError(token, "';' after declaration", NULL);
		return false;
	}

	incrementToken(token);

	return true;
}

bool validateDeclaration(Declaration *node, LocalSymbolTable *localTable)
{
	bool success = true;

	if (!symbolTableDeclareLocal(localTable, SYMBOL_VARIABLE, node->variableId))
		success = false;

	Variable *variable = symbolTableGetVariable(node->variableId);
	
	if (!validateVariable(variable, localTable))
		success = false;

	if (!validateExpression(&node->value, localTable))
		success = false;
	
	if (!success)
		return false;

	Type *variableType = variable->isExplicitlyTyped
		? &variable->annotation.type
		: NULL;

	Type expressionType;
	if (!expressionGetType(&expressionType, &node->value, variableType))
		return false;

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

void declarationFree(Declaration *node)
{
	expressionFree(&node->value);
}
