#include "parka/ast/ExpressionStatement.hpp"
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

		auto snippet = expression->snippet() + Snippet(token);

		token.increment();

		auto *syntax = new ExpressionStatementSyntax(snippet, *expression);

		return syntax;
	}

	StatementContext *ExpressionStatementSyntax::validate(SymbolTable&)
	{
		log::notImplemented(here());
	}
}
