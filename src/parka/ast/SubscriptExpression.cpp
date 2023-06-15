#include "parka/ast/SubscriptExpression.hpp"
#include "parka/log/Log.hpp"
#include "parka/ast/Expression.hpp"

namespace parka
{
	SubscriptExpressionSyntax::SubscriptExpressionSyntax(ExpressionSyntax& primary, ExpressionSyntax& index) :
	_primary(primary),
	_index(index)
	{}

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

		auto *syntax = new SubscriptExpressionSyntax(primary, *index);

		if (token.type() != TokenType::RightBracket)
		{
			log::parseError(token, "']' after subscript");
			return {};
		}

		token.increment();

		return syntax;
	}

	ExpressionContext *SubscriptExpressionSyntax::validate(SymbolTable& symbolTable)
	{
		log::notImplemented(here());
	}
}