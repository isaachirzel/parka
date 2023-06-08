#include "parka/syntax/BitwiseXorExpressionSyntax.hpp"
#include "parka/syntax/BitwiseAndExpressionSyntax.hpp"

#include "parka/util/Print.hpp"

namespace parka
{
	const ExpressionSyntax *BitwiseXorExpressionSyntax::parse(Token& token)
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
			auto& syntax = ExpressionSyntax::create(std::move(expression));

			lhs = &syntax;
		}

		return lhs;
	}
}
