#include "parka/ast/subscript_expression.hpp"
#include "parka/node/node_bank.hpp"
#include "parka/token.hpp"
#include "parka/util/print.hpp"

Optional<ExpressionId> IndexExpression::parse(Token& token, ExpressionId primary)
{
	if (token.type() != TokenType::LeftBracket)
	{
		printParseError(token, "'['");
		return {};
	}

	token.increment();

	auto index = Expression::parse(token);

	if (!index)
		return {};

	auto expression = IndexExpression(std::move(primary), *index);
	auto id = NodeBank::add(std::move(expression));

	if (token.type() != TokenType::RightBracket)
	{
		printParseError(token, "']' after subscript");
		return {};
	}

	token.increment();

	return id;
}

bool IndexExpression::validate(const EntityId&)
{
	exitNotImplemented(here());
}

Optional<Type> IndexExpression::getType() const
{
	exitNotImplemented(here());
}
