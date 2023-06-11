#include "parka/syntax/ExpressionStatementSyntax.hpp"
#include "parka/log/Log.hpp"

namespace parka
{
	StatementSyntax *ExpressionStatementSyntax::parse(Token& token)
	{
		auto expression = ExpressionSyntax::parse(token);

		if (!expression)
			return {};

		if (token.type() != TokenType::Semicolon)
		{
			log::parseError(token, "';' after expression statement");
			return {};
		}

		token.increment();

		auto *syntax = new ExpressionStatementSyntax(*expression);

		return syntax;
	}
}
