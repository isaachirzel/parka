#include "parka/syntax/ExpressionStatementSyntax.hpp"
#include "parka/data/ExpressionId.hpp"
#include "parka/Storage.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	Optional<StatementId> ExpressionStatementSyntax::parse(Token& token)
	{
		auto expression = ExpressionSyntax::parse(token);

		if (!expression)
			return {};

		if (token.type() != TokenType::Semicolon)
		{
			printParseError(token, "';' after expression statement", NULL);
			return {};
		}

		token.increment();

		auto statement = ExpressionStatementSyntax(*expression);
		auto id = Storage::add(std::move(statement));

		return id;
	}
}
