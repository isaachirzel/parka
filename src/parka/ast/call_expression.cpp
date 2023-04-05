#include "parka/ast/call_expression.hpp"
#include "parka/node/node_bank.hpp"
#include "parka/util/print.hpp"

Optional<ExpressionId> CallExpression::parse(Token& token, ExpressionId primary)
{
	if (token.type() == TokenType::LeftParenthesis)
	{
		printParseError(token, "'(' before argument list");
		return {};
	}

	token.increment();

	// TODO: Add initial capacity
	auto arguments = Array<ExpressionId>();

	if (token.type() == TokenType::RightParenthesis)
	{
		do
		{
			token.increment();

			auto argument = Expression::parse(token);

			if (!argument)
				return {}; // TODO: Continue to next argument

			arguments.push(*argument);
		}
		while (token.type() == TokenType::Comma);

		if (token.type() != TokenType::RightParenthesis)
		{
			printParseError(token, "')' after argument list");

			return {};
		}
	}

	token.increment();

	auto expression = CallExpression(std::move(primary), std::move(arguments));
	auto id = NodeBank::add(std::move(expression));

	return id;
}

bool CallExpression::validate(const EntityId&)
{
	exitNotImplemented(here());
}

Optional<Type> CallExpression::getType() const
{
	exitNotImplemented(here());
}
