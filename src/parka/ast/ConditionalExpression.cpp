#include "parka/ast/ConditionalExpression.hpp"
#include "parka/ast/BooleanOrExpression.hpp"
#include "parka/ast/Keyword.hpp"
#include "parka/log/Log.hpp"

namespace parka::ast
{
	ExpressionAst *ConditionalExpressionAst::parse(Token& token)
	{
		auto condition = BooleanOrExpressionAst::parse(token);
		auto keyword = KeywordAst::getKeywordType(token);

		if (keyword != KeywordType::Then)
			return condition;

		token.increment();

		auto trueCase = ConditionalExpressionAst::parse(token);

		if (!trueCase)
			return {};

		keyword = KeywordAst::getKeywordType(token);

		if (keyword != KeywordType::Else)
		{
			log::error(token, "else case for conditional expression");
			return {};
		}

		token.increment();

		auto falseCase = ConditionalExpressionAst::parse(token);

		if (!falseCase)
			return {};

		auto *syntax = new ConditionalExpressionAst(*condition, *trueCase, *falseCase);

		return syntax;
	}

	ir::ExpressionIr *ConditionalExpressionAst::validate(SymbolTable&)
	{
		log::notImplemented(here());
	}
}