#include "parka/ast/SubscriptExpression.hpp"
#include "parka/log/Log.hpp"
#include "parka/ast/Expression.hpp"

namespace parka::ast
{
	SubscriptExpressionAst::

	ExpressionAst *SubscriptExpressionAst::parse(Token& token, ExpressionAst& primary)
	{
		if (token.type() != TokenType::LeftBracket)
		{
			log::parseError(token, "'['");
			return {};
		}

		token.increment();

		auto index = ExpressionAst::parse(token);

		if (!index)
			return {};


		if (token.type() != TokenType::RightBracket)
		{
			log::parseError(token, "']' after subscript");
			return {};
		}

		auto snippet = primary.snippet() + Snippet(token);
		auto *syntax = new SubscriptExpressionAst(snippet, primary, *index);

		token.increment();

		return syntax;
	}

	ir::ExpressionIr *SubscriptExpressionAst::validate(SymbolTable&)
	{
		log::notImplemented(here());
	}
}