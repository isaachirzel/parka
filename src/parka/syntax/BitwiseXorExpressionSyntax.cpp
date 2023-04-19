#include "parka/syntax/BitwiseXorExpressionSyntax.hpp"
#include "parka/syntax/BitwiseAndExpressionSyntax.hpp"

#include "parka/util/Print.hpp"

namespace parka
{
	Optional<ExpressionSyntaxId> BitwiseXorExpressionSyntax::parse(Token& token)
	{
		auto lhs = BitwiseAndExpressionSyntax::parse(token);

		if (!lhs)
			return {};

		while (token.type() == TokenType::Carrot)
		{
			token.increment();

			auto rhs = BitwiseAndExpressionSyntax::parse(token);

			if (!rhs)
				return {};

			auto expression = BitwiseXorExpressionSyntax(*lhs, *rhs);
			auto id = ExpressionSyntaxId::create(std::move(expression));

			lhs = std::move(id);
		}

		return lhs;
	}
}
