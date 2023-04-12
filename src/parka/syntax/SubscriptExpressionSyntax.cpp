#include "parka/syntax/SubscriptExpressionSyntax.hpp"
#include "parka/repository/SyntaxRepository.hpp"
#include "parka/Token.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	Optional<ExpressionSyntaxId> SubscriptExpressionSyntax::parse(Token& token, ExpressionSyntaxId primary)
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
		auto id = SyntaxRepository::add(std::move(expression));

		if (token.type() != TokenType::RightBracket)
		{
			printParseError(token, "']' after subscript");
			return {};
		}

		token.increment();

		return id;
	}
}
