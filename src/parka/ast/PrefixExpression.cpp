#include "parka/ast/PrefixExpression.hpp"
#include "parka/log/Log.hpp"
#include "parka/ast/PostfixExpression.hpp"

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
		auto start = Snippet(token);
		auto type = parsePrefixType(token);

		if (!type)
			return PostfixExpressionSyntax::parse(token);

		token.increment();

		auto *inner = PrefixExpressionSyntax::parse(token);

		if (inner == nullptr)
			return nullptr;

		auto snippet = start + inner->snippet();
		auto *syntax = new PrefixExpressionSyntax(snippet, *type, *inner);

		return syntax;
	}

	ExpressionContext *PrefixExpressionSyntax::validate(SymbolTable&)
	{
		log::notImplemented(here());
	}
}