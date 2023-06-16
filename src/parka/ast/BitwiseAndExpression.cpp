#include "parka/ast/BitwiseAndExpression.hpp"
#include "parka/log/Log.hpp"
#include "parka/ast/EqualityExpression.hpp"

namespace parka::ast
{
	ExpressionAst *BitwiseAndExpressionAst::parse(Token& token)
	{
		auto *lhs = EqualityExpressionAst::parse(token);

		if (!lhs)
			return {};

		while (token.type() == TokenType::Ampersand)
		{
			token.increment();

			auto rhs = EqualityExpressionAst::parse(token);

			if (!rhs)
				return {};

			lhs = new BitwiseAndExpressionAst(*lhs, *rhs);
		}

		return lhs;
	}

	ir::ExpressionIr *BitwiseAndExpressionAst::validate(SymbolTable&)
	{
		log::notImplemented(here());
	}
}
