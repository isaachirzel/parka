#include "parka/syntax/BitwiseOrExpressionSyntax.hpp"
#include "parka/syntax/BitwiseXorExpressionSyntax.hpp"
#include "parka/repository/SyntaxRepository.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	Optional<ExpressionSyntaxId> BitwiseOrExpressionSyntax::parse(Token& token)
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
			auto id = SyntaxRepository::add(std::move(expression));

			lhs = std::move(id);
		}

		return lhs;
	}
}
