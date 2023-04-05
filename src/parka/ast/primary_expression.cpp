#include "parka/ast/primary_expression.hpp"
#include "parka/ast/expression.hpp"
#include "parka/ast/identifier_expression.hpp"
#include "parka/ast/literal.hpp"
#include "parka/node/node_bank.hpp"
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
			return IdentifierExpression::parse(token);

		case TokenType::LeftParenthesis:
			return parseEnclosedExpression(token);

		default:
			return Literal::parse(token);
	}
}
