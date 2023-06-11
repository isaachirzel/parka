#include "parka/syntax/BitwiseOrExpressionSyntax.hpp"
#include "parka/syntax/BitwiseXorExpressionSyntax.hpp"

namespace parka
{
	ExpressionSyntax *BitwiseOrExpressionSyntax::parse(Token& token)
	{
		auto *lhs = BitwiseXorExpressionSyntax::parse(token);

		if (!lhs)
			return {};

		while (token.type() == TokenType::Pipe)
		{
			token.increment();

			auto rhs = BitwiseXorExpressionSyntax::parse(token);

			if (!rhs)
				return {};

			lhs = new BitwiseOrExpressionSyntax(*lhs, *rhs);
		}

		return lhs;
	}
}
