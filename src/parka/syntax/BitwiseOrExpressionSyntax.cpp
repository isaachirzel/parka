#include "parka/syntax/BitwiseOrExpressionSyntax.hpp"
#include "parka/syntax/BitwiseXorExpressionSyntax.hpp"

#include "parka/util/Print.hpp"

namespace parka
{
	const ExpressionSyntax *BitwiseOrExpressionSyntax::parse(Token& token)
	{
		auto lhs = BitwiseXorExpressionSyntax::parse(token);

		if (!lhs)
			return {};

		while (token.type() == TokenType::Pipe)
		{
			token.increment();

			auto rhs = BitwiseXorExpressionSyntax::parse(token);

			if (!rhs)
				return {};

			auto expression = BitwiseOrExpressionSyntax(*lhs, *rhs);
			auto& syntax = ExpressionSyntax::create(std::move(expression));

			lhs = &syntax;
		}

		return lhs;
	}
}
