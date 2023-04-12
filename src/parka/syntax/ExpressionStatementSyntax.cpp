#include "parka/syntax/ExpressionStatementSyntax.hpp"
#include "parka/repository/ExpressionSyntaxId.hpp"
#include "parka/repository/SyntaxRepository.hpp"
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
			printParseError(token, "';' after expression statement", NULL);
			return {};
		}

		token.increment();

		auto statement = ExpressionStatementSyntax(*expression);
		auto id = SyntaxRepository::add(std::move(statement));

		return id;
	}
}