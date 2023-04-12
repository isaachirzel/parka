#include "parka/syntax/BooleanOrExpressionSyntax.hpp"
#include "parka/syntax/BooleanAndExpressionSyntax.hpp"
#include "parka/repository/SyntaxRepository.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	Optional<ExpressionSyntaxId> BooleanOrExpressionSyntax::parse(Token& token)
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
			auto id = SyntaxRepository::add(std::move(expression));

			lhs = std::move(id);
		}

		return lhs;
	}
}
