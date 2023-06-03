
#include "parka/syntax/PrefixExpressionSyntax.hpp"
#include "parka/syntax/ExpressionSyntax.hpp"
#include "parka/syntax/PostfixExpressionSyntax.hpp"
#include "parka/syntax/PrimaryExpressionSyntax.hpp"

#include "parka/util/Print.hpp"

namespace parka
{
	Optional<PrefixType> parsePrefixType(Token& token)
	{
		switch (token.type())
		{
			case TokenType::Ampersand:
				return PrefixType::Reference;

			case TokenType::Asterisk:
				return PrefixType::Dereference;

			case TokenType::Plus:
				return PrefixType::Positive;

			case TokenType::Minus:
				return PrefixType::Negative;

			case TokenType::BitwiseNot:
				return PrefixType::BitwiseNot;

			case TokenType::BooleanNot:
				return PrefixType::BooleanNot;

			default:
				return {};
		}
	}

	Optional<ExpressionSyntaxId> PrefixExpressionSyntax::parse(Token& token)
	{
		auto type = parsePrefixType(token);

		if (!type)
			return PostfixExpressionSyntax::parse(token);

		auto prefixToken = token;

		token.increment();

		auto inner = PrefixExpressionSyntax::parse(token);
		auto expression = PrefixExpressionSyntax(*type, *inner, prefixToken);
		auto id = ExpressionSyntaxId::create(std::move(expression));

		return id;
	}
}
