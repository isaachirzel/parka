#include "parka/ast/BooleanOrExpression.hpp"
#include "parka/log/Log.hpp"
#include "parka/ast/BooleanAndExpression.hpp"

namespace parka::ast
{
	ExpressionAst *BooleanOrExpressionAst::parse(Token& token)
	{
		auto *lhs = BooleanAndExpressionAst::parse(token);

		if (!lhs)
			return {};

		while (token.type() == TokenType::BooleanOr)
		{
			token.increment();

			auto rhs = BooleanAndExpressionAst::parse(token);

			if (!rhs)
				return {};
			
			lhs = new BooleanOrExpressionAst(*lhs, *rhs);
		}


		return lhs;
	}

	ir::ExpressionIr *BooleanOrExpressionAst::validate(SymbolTable&)
	{
		log::notImplemented(here());
	}
}