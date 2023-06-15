#include "parka/ast/ExpressionStatement.hpp"
#include "parka/log/Log.hpp"

namespace parka
{
	ExpressionStatementSyntax::ExpressionStatementSyntax(ExpressionSyntax& expression) :
	_expression(expression)
	{}

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

	StatementContext *ExpressionStatementSyntax::validate(SymbolTable&)
	{
		log::notImplemented(here());
	}
}
