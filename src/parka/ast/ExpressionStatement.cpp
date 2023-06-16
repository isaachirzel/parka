#include "parka/ast/ExpressionStatement.hpp"
#include "parka/log/Log.hpp"

namespace parka::ast
{
	StatementAst *ExpressionStatementAst::parse(Token& token)
	{
		auto expression = ExpressionAst::parse(token);

		if (!expression)
			return {};

		if (token.type() != TokenType::Semicolon)
		{
			log::parseError(token, "';' after expression statement");
			return {};
		}

		auto snippet = expression->snippet() + Snippet(token);

		token.increment();

		auto *syntax = new ExpressionStatementAst(snippet, *expression);

		return syntax;
	}

	ir::StatementIr *ExpressionStatementAst::validate(SymbolTable&)
	{
		log::notImplemented(here());
	}
}
