#include "parka/ast/BitwiseXorExpression.hpp"
#include "parka/log/Log.hpp"
#include "parka/ast/BitwiseAndExpression.hpp"

namespace parka::ast
{
	ExpressionAst *BitwiseXorExpressionAst::parse(Token& token)
	{
		auto *lhs = BitwiseAndExpressionAst::parse(token);

		if (!lhs)
			return {};

		while (token.type() == TokenType::Carrot)
		{
			token.increment();

			auto rhs = BitwiseAndExpressionAst::parse(token);

			if (!rhs)
				return {};

			lhs = new BitwiseXorExpressionAst(*lhs, *rhs);
		}

		return lhs;
	}

	ir::ExpressionIr *BitwiseXorExpressionAst::validate(SymbolTable&)
	{
		log::notImplemented(here());
	}
}
