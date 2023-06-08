#include "parka/syntax/BitwiseAndExpressionSyntax.hpp"
#include "parka/syntax/EqualityExpressionSyntax.hpp"
#include "parka/syntax/ExpressionSyntax.hpp"

#include "parka/Token.hpp"
#include "parka/util/Optional.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	const ExpressionSyntax *BitwiseAndExpressionSyntax::parse(Token& token)
	{
		auto lhs = EqualityExpressionSyntax::parse(token);

		if (!lhs)
			return {};

		while (token.type() == TokenType::Ampersand)
		{
			token.increment();

			auto rhs = EqualityExpressionSyntax::parse(token);

			if (!rhs)
				return {};

			auto expression = BitwiseAndExpressionSyntax(*lhs, *rhs);
			auto& syntax = ExpressionSyntax::create(std::move(expression));

			lhs = &syntax;
		}

		return lhs;
	}
}
