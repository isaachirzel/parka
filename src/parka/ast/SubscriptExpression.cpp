#include "parka/ast/SubscriptExpression.hpp"
#include "parka/log/Log.hpp"
#include "parka/ast/Expression.hpp"

namespace parka
{
	SubscriptExpressionSyntax::

	ExpressionSyntax *SubscriptExpressionSyntax::parse(Token& token, ExpressionSyntax& primary)
	{
		if (token.type() != TokenType::LeftBracket)
		{
			log::parseError(token, "'['");
			return {};
		}

		token.increment();

		auto index = ExpressionSyntax::parse(token);

		if (!index)
			return {};


		if (token.type() != TokenType::RightBracket)
		{
			log::parseError(token, "']' after subscript");
			return {};
		}

		auto snippet = primary.snippet() + Snippet(token);
		auto *syntax = new SubscriptExpressionSyntax(snippet, primary, *index);

		token.increment();

		return syntax;
	}

	ExpressionContext *SubscriptExpressionSyntax::validate(SymbolTable&)
	{
		log::notImplemented(here());
	}
}