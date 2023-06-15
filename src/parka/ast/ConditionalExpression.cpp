#include "parka/ast/ConditionalExpression.hpp"
#include "parka/ast/BooleanOrExpression.hpp"
#include "parka/ast/Keyword.hpp"
#include "parka/log/Log.hpp"

namespace parka
{
	ExpressionSyntax *ConditionalExpressionSyntax::parse(Token& token)
	{
		auto condition = BooleanOrExpressionSyntax::parse(token);
		auto keyword = KeywordSyntax::getKeywordType(token);

		if (keyword != KeywordType::Then)
			return condition;

		token.increment();

		auto trueCase = ConditionalExpressionSyntax::parse(token);

		if (!trueCase)
			return {};

		keyword = KeywordSyntax::getKeywordType(token);

		if (keyword != KeywordType::Else)
		{
			log::error(token, "else case for conditional expression");
			return {};
		}

		token.increment();

		auto falseCase = ConditionalExpressionSyntax::parse(token);

		if (!falseCase)
			return {};

		auto *syntax = new ConditionalExpressionSyntax(*condition, *trueCase, *falseCase);

		return syntax;
	}

	ExpressionContext *ConditionalExpressionSyntax::validate(SymbolTable&)
	{
		log::notImplemented(here());
	}
}