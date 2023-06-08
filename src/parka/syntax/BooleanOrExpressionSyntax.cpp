#include "parka/syntax/BooleanOrExpressionSyntax.hpp"
#include "parka/syntax/BooleanAndExpressionSyntax.hpp"

#include "parka/util/Print.hpp"

namespace parka
{
	const ExpressionSyntax *BooleanOrExpressionSyntax::parse(Token& token)
	{
		auto lhs = BooleanAndExpressionSyntax::parse(token);

		if (!lhs)
			return {};

		while (token.type() == TokenType::BooleanOr)
		{
			token.increment();

			auto rhs = BooleanAndExpressionSyntax::parse(token);

			if (!rhs)
				return {};

			auto expression = BooleanOrExpressionSyntax(*lhs, *rhs);
			auto& syntax = ExpressionSyntax::create(std::move(expression));

			lhs = &syntax;
		}

		return lhs;
	}
}
