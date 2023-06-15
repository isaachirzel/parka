#include "parka/ast/PrimaryExpression.hpp"
#include "parka/log/Log.hpp"
#include "parka/ast/Expression.hpp"
#include "parka/ast/IdentifierExpression.hpp"
#include "parka/ast/Literal.hpp"

#include "parka/util/Print.hpp"

namespace parka
{
	static ExpressionSyntax *parseEnclosedExpressionSyntax(Token& token)
	{
		token.increment();

		auto *expression = ExpressionSyntax::parse(token);

		if (!expression)
			return {};

		if (token.type() != TokenType::RightParenthesis)
		{
			log::parseError(token, "expected ')' after primary sub-expression");
			return {};
		}

		return expression;
	}

	ExpressionSyntax *PrimaryExpressionSyntax::parse(Token& token)
	{
		switch (token.type())
		{
			case TokenType::Identifier:
				return IdentifierExpressionSyntax::parse(token);

			case TokenType::LeftParenthesis:
				return parseEnclosedExpressionSyntax(token);

			default:
				return LiteralSyntax::parse(token);
		}
	}
}
