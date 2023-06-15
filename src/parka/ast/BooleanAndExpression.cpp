#include "parka/ast/BooleanAndExpression.hpp"
#include "parka/log/Log.hpp"
#include "parka/ast/BitwiseOrExpression.hpp"

namespace parka
{
	ExpressionSyntax *BooleanAndExpressionSyntax::parse(Token& token)
	{
		auto *lhs = BitwiseOrExpressionSyntax::parse(token);

		if (!lhs)
			return {};

		while (token.type() == TokenType::BooleanAnd)
		{
			token.increment();

			auto rhs = BitwiseOrExpressionSyntax::parse(token);

			if (!rhs)
				return {};

			lhs = new BooleanAndExpressionSyntax(*lhs, *rhs);
		}

		return lhs;
	}

	ExpressionContext *BooleanAndExpressionSyntax::validate(SymbolTable& symbolTable)
	{
		log::notImplemented(here());
	}
}
