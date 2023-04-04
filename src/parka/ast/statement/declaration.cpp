#include "parka/ast/expression/expression.hpp"
#include "parka/ast/function/function.hpp"
#include "parka/ast/module.hpp"
#include "parka/ast/statement/declaration.hpp"
#include "parka/ast/function/variable.hpp"
#include "parka/symbol/node_bank.hpp"
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

	auto declaration = Declaration(variableId.unwrap(), value.unwrap());
	auto id = NodeBank::add(std::move(declaration));

	return id;
}

bool Declaration::validate(const EntityId& functionId)
{
	auto success = true;
	auto& function = NodeBank::getFunction(functionId);
	auto& variable = NodeBank::getVariable(_variableId);
	
	if (!variable.validate(functionId))
		success = false;

	if (!function.declare(_variableId))
		success = false;

	auto& value = NodeBank::get(_value);

	if (!value.validate(functionId))
		success = false;

	// TODO: Validate type conversion

	return success;
}
