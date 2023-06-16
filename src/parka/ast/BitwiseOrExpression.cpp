#include "parka/ast/BitwiseOrExpression.hpp"
#include "parka/log/Log.hpp"
#include "parka/ast/BitwiseXorExpression.hpp"

namespace parka::ast
{
	ExpressionAst *BitwiseOrExpressionAst::parse(Token& token)
	{
		auto *lhs = BitwiseXorExpressionAst::parse(token);

		if (!lhs)
			return {};

		while (token.type() == TokenType::Pipe)
		{
			token.increment();

			auto rhs = BitwiseXorExpressionAst::parse(token);

			if (!rhs)
				return {};
			
			lhs = new BitwiseOrExpressionAst(*lhs, *rhs);
		}

		return lhs;
	}

	ir::ExpressionIr *BitwiseOrExpressionAst::validate(SymbolTable&)
	{
		log::notImplemented(here());
	}
}
