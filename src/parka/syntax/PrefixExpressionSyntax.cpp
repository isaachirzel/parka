#include "parka/syntax/PrefixExpressionSyntax.hpp"
#include "parka/log/Log.hpp"
#include "parka/syntax/PostfixExpressionSyntax.hpp"

namespace parka
{
	static Optional<PrefixType> parsePrefixType(Token& token)
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

	ExpressionSyntax *PrefixExpressionSyntax::parse(Token& token)
	{
		auto type = parsePrefixType(token);

		if (!type)
			return PostfixExpressionSyntax::parse(token);

		auto prefixToken = token;

		token.increment();

		auto *inner = PrefixExpressionSyntax::parse(token);
		auto *syntax = new PrefixExpressionSyntax(*type, *inner, prefixToken);

		return syntax;
	}

	ExpressionContext *PrefixExpressionSyntax::validate(SymbolTable& symbolTable)
	{
		log::notImplemented(here());
	}
}