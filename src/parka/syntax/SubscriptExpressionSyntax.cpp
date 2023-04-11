#include "parka/syntax/SubscriptExpressionSyntax.hpp"
#include "parka/Storage.hpp"
#include "parka/Token.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	Optional<ExpressionId> SubscriptExpressionSyntax::parse(Token& token, ExpressionId primary)
	{
		if (token.type() != TokenType::LeftBracket)
		{
			printParseError(token, "'['");
			return {};
		}

		token.increment();

		auto index = ExpressionSyntax::parse(token);

		if (!index)
			return {};

		auto expression = SubscriptExpressionSyntax(std::move(primary), *index);
		auto id = Storage::add(std::move(expression));

		if (token.type() != TokenType::RightBracket)
		{
			printParseError(token, "']' after subscript");
			return {};
		}

		token.increment();

		return id;
	}
}
