#include "parka/syntax/SubscriptExpressionSyntax.hpp"

#include "parka/Token.hpp"
#include "parka/log/Log.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	const ExpressionSyntax *SubscriptExpressionSyntax::parse(Token& token, const ExpressionSyntax& primary)
	{
		if (token.type() != TokenType::LeftBracket)
		{
			log::parseError(token, "'['");
			return {};
		}

		token.increment();

		auto index = ExpressionSyntax::parse(token);

		if (!index)
			return {};

		auto expression = SubscriptExpressionSyntax(primary, *index);
		auto& syntax = ExpressionSyntax::create(std::move(expression));

		if (token.type() != TokenType::RightBracket)
		{
			log::parseError(token, "']' after subscript");
			return {};
		}

		token.increment();

		return &syntax;
	}
}
