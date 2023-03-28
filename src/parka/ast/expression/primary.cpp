#include "parka/ast/expression/primary.hpp"
#include "parka/ast/expression/expression.hpp"
#include "parka/ast/expression/identifier.hpp"
#include "parka/ast/expression/literal/literal.hpp"
#include "parka/symbol/node_bank.hpp"
#include "parka/util/print.hpp"

Optional<ExpressionId> parseEnclosedExpression(Token& token)
{
	token.increment();

	auto expression = Expression::parse(token);

	if (!expression)
		return {};

	if (token.type() != TokenType::RightParenthesis)
	{
		printParseError(token, "expected ')' after primary sub-expression");
		return {};
	}

	return expression;
}

Optional<ExpressionId> PrimaryExpression::parse(Token& token)
{
	switch (token.type())
	{
		case TokenType::Identifier:
			return Identifier::parse(token);

		case TokenType::LeftParenthesis:
			return parseEnclosedExpression(token);

		default:
			return Literal::parse(token);
	}
}
