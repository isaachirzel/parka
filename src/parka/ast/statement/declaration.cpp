#include "parka/ast/expression/expression.hpp"
#include "parka/ast/statement/declaration.hpp"
#include "parka/ast/variable.hpp"
#include "parka/symbol_table.hpp"
#include "parka/util/print.hpp"

bool parseDeclaration(Declaration *node, Token& token)
{
	node->variableId = symbolTableAddVariable();
	Variable *variable = symbolTableGetVariable(node->variableId);

	if (!parseVariable(variable, token))
		return false;

	if (token.type() != TokenType::Assign)
	{
		printParseError(token, "expected '=' after declaration", NULL);
		return false;
	}

	token.increment();

	if (!parseExpression(&node->value, token))
		return false;

	if (token.type() != TokenType::Semicolon)
	{
		printFmt("TOKEN: %zu, %s", token.length(), tokenGetText(token));

		printParseError(token, "';' after declaration", NULL);
		return false;
	}

	token.increment();

	return true;
}

bool validateDeclaration(Declaration *node, SymbolTable& localTable)
{
	bool success = true;

	if (!symbolTableDeclareLocal(localTable, EntityType::Variable, node->variableId))
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
		Type& variableType = &variable->annotation.type;

		if (!typeCanConvert(variableType, &expressionType))
		{
			auto toTypeName = expressionType.getName();
			auto fromTypeName = variableTypegetName();

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
