#include "parka/ast/expression.hpp"
#include "parka/ast/function.hpp"
#include "parka/ast/module.hpp"
#include "parka/ast/declaration_statement.hpp"
#include "parka/ast/variable.hpp"
#include "parka/node/node_bank.hpp"
#include "parka/util/print.hpp"

Optional<StatementId> Declaration::parse(Token& token)
{
	auto variableId = Variable::parse(token);

	if (!variableId)
		return {};

	if (token.type() != TokenType::Assign)
	{
		printParseError(token, "expected '=' after declaration", NULL);
		return {};
	}

	token.increment();

	auto value = Expression::parse(token);

	if (!value)
		return {};

	if (token.type() != TokenType::Semicolon)
	{
		printParseError(token, "';'", "Declaration statements need to be ended with a ';'.");
		return {};
	}

	token.increment();

	auto declaration = Declaration(*variableId, *value);
	auto id = NodeBank::add(std::move(declaration));

	return id;
}

bool Declaration::validate(const EntityId& functionId)
{
	auto success = true;
	auto& function = NodeBank::getFunction(functionId);
	auto& variable = NodeBank::getVariable(_variableId);
	auto& value = NodeBank::get(_value);
	
	if (!value.validate(functionId))
		success = false;

	if (!variable.validate(functionId))
		success = false;

	// The declaration comes after expression validation so it can't access the declaration
	if (!function.declare(_variableId))
		success = false;

	if (!success)
		return false;

	auto valueType = value.getType();

	if (!valueType)
		return false;

	auto variableType = variable.getType();

	if (variableType)
	{
		if (!valueType->canConvertTo(*variableType))
		{
			printError("Unable to initialize $ with $", *variableType, *valueType);
			return false;
		}
	}
	else
	{
		variable.setType(*valueType);
	}

	return true;
}
