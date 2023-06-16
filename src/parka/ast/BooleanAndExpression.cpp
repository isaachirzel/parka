#include "parka/ast/BooleanAndExpression.hpp"
#include "parka/log/Log.hpp"
#include "parka/ast/BitwiseOrExpression.hpp"

namespace parka::ast
{
	ExpressionAst *BooleanAndExpressionAst::parse(Token& token)
	{
		auto *lhs = BitwiseOrExpressionAst::parse(token);

		if (!lhs)
			return {};

		while (token.type() == TokenType::BooleanAnd)
		{
			token.increment();

			auto rhs = BitwiseOrExpressionAst::parse(token);

			if (!rhs)
				return {};

			lhs = new BooleanAndExpressionAst(*lhs, *rhs);
		}

		return lhs;
	}

	ir::ExpressionIr *BooleanAndExpressionAst::validate(SymbolTable&)
	{
		log::notImplemented(here());
	}
}
