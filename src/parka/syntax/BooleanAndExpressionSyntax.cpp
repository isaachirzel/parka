#include "parka/syntax/BooleanAndExpressionSyntax.hpp"
#include "parka/syntax/BitwiseOrExpressionSyntax.hpp"

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
}
