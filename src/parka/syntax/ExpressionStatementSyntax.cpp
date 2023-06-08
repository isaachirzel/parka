#include "parka/syntax/ExpressionStatementSyntax.hpp"
#include "parka/log/Log.hpp"

namespace parka
{
	const StatementSyntax *ExpressionStatementSyntax::parse(Token& token)
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

		auto statement = ExpressionStatementSyntax(*expression);
		auto& syntax = StatementSyntax::create(std::move(statement));

		return &syntax;
	}
}
