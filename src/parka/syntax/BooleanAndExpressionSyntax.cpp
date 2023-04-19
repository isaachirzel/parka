#include "parka/syntax/BooleanAndExpressionSyntax.hpp"
#include "parka/syntax/BitwiseOrExpressionSyntax.hpp"
#include "parka/syntax/ExpressionSyntax.hpp"

#include "parka/util/Print.hpp"

namespace parka
{
	Optional<ExpressionSyntaxId> BooleanAndExpressionSyntax::parse(Token& token)
	{
		auto lhs = BitwiseOrExpressionSyntax::parse(token);

		if (!lhs)
			return {};

		while (token.type() == TokenType::BooleanAnd)
		{
			token.increment();

			auto rhs = BitwiseOrExpressionSyntax::parse(token);

			if (!rhs)
				return {};

			auto expression = BooleanAndExpressionSyntax(*lhs, *rhs);
			auto id = ExpressionSyntaxId::create(std::move(expression));

			lhs = std::move(id);
		}

		return lhs;
	}
}
