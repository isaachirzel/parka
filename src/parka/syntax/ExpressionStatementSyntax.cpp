#include "parka/syntax/ExpressionStatementSyntax.hpp"
#include "parka/log/Log.hpp"
#include "parka/repository/ExpressionSyntaxId.hpp"

#include "parka/util/Print.hpp"

namespace parka
{
	Optional<StatementSyntaxId> ExpressionStatementSyntax::parse(Token& token)
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
		auto id = StatementSyntaxId::create(std::move(statement));

		return id;
	}
}
