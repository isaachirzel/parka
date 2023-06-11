#include "parka/syntax/BitwiseXorExpressionSyntax.hpp"
#include "parka/syntax/BitwiseAndExpressionSyntax.hpp"

namespace parka
{
	BitwiseXorExpressionSyntax::BitwiseXorExpressionSyntax(ExpressionSyntax& lhs, ExpressionSyntax& rhs) :
	_lhs(lhs),
	_rhs(rhs)
	{}

	ExpressionSyntax *BitwiseXorExpressionSyntax::parse(Token& token)
	{
		auto *lhs = BitwiseAndExpressionSyntax::parse(token);

		if (!lhs)
			return {};

		while (token.type() == TokenType::Carrot)
		{
			token.increment();

			auto rhs = BitwiseAndExpressionSyntax::parse(token);

			if (!rhs)
				return {};

			lhs = new BitwiseXorExpressionSyntax(*lhs, *rhs);
		}

		return lhs;
	}
}
