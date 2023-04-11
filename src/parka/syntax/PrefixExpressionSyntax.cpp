
#include "parka/syntax/PrefixExpressionSyntax.hpp"
#include "parka/syntax/ExpressionSyntax.hpp"
#include "parka/syntax/PostfixExpressionSyntax.hpp"
#include "parka/syntax/PrimaryExpressionSyntax.hpp"
#include "parka/Storage.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	Optional<PrefixExpressionSyntaxType> parsePrefixExpressionSyntaxType(Token& token)
	{
		switch (token.type())
		{
			case TokenType::Ampersand:
				return PrefixExpressionSyntaxType::Reference;

			case TokenType::Asterisk:
				return PrefixExpressionSyntaxType::Dereference;

			case TokenType::Plus:
				return PrefixExpressionSyntaxType::Positive;

			case TokenType::Minus:
				return PrefixExpressionSyntaxType::Negative;

			case TokenType::BitwiseNot:
				return PrefixExpressionSyntaxType::BitwiseNot;

			case TokenType::BooleanNot:
				return PrefixExpressionSyntaxType::BooleanNot;

			default:
				return {};
		}
	}

	Optional<ExpressionId> PrefixExpressionSyntax::parse(Token& token)
	{
		auto type = parsePrefixExpressionSyntaxType(token);

		if (!type)
			return PrimaryExpressionSyntax::parse(token);

		auto prefixToken = token;

		token.increment();

		auto inner = PrefixExpressionSyntax::parse(token);
		auto expression = PrefixExpressionSyntax(*type, *inner, prefixToken);
		auto id = Storage::add(std::move(expression));

		return id;
	}
}
