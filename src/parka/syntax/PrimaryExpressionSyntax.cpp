#include "parka/syntax/PrimaryExpressionSyntax.hpp"
#include "parka/syntax/ExpressionSyntax.hpp"
#include "parka/syntax/IdentifierExpressionSyntax.hpp"
#include "parka/syntax/LiteralSyntax.hpp"
#include "parka/Storage.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	Optional<ExpressionId> parseEnclosedExpressionSyntax(Token& token)
	{
		token.increment();

		auto expression = ExpressionSyntax::parse(token);

		if (!expression)
			return {};

		if (token.type() != TokenType::RightParenthesis)
		{
			printParseError(token, "expected ')' after primary sub-expression");
			return {};
		}

		return expression;
	}

	Optional<ExpressionId> PrimaryExpressionSyntax::parse(Token& token)
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
