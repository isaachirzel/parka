#include "parka/syntax/SubscriptExpressionSyntax.hpp"

#include "parka/Token.hpp"
#include "parka/log/Log.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	Optional<ExpressionSyntaxId> SubscriptExpressionSyntax::parse(Token& token, ExpressionSyntaxId primary)
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

		auto expression = SubscriptExpressionSyntax(std::move(primary), *index);
		auto id = ExpressionSyntaxId::create(std::move(expression));

		if (token.type() != TokenType::RightBracket)
		{
			log::parseError(token, "']' after subscript");
			return {};
		}

		token.increment();

		return id;
	}
}
