#include "parka/syntax/EqualityExpressionSyntax.hpp"
#include "parka/syntax/RelationalExpressionSyntax.hpp"

#include "parka/util/Print.hpp"

namespace parka
{
	Optional<EqualityType> getEqualityType(Token& token)
	{
		switch (token.type())
		{
			case TokenType::Equals:
				return EqualityType::Equals;

			case TokenType::NotEquals:
				return EqualityType::NotEquals;

			default:
				return {};
		}
	}

	const ExpressionSyntax *EqualityExpressionSyntax::parse(Token& token)
	{
		auto lhs = RelationalExpressionSyntax::parse(token);

		if (!lhs)
			return {};

		auto type = getEqualityType(token);

		while (type)
		{
			token.increment();

			auto rhs = RelationalExpressionSyntax::parse(token);

			if (!rhs)
				return {};

			auto expression = EqualityExpressionSyntax(*lhs, *rhs, *type);
			auto& syntax = ExpressionSyntax::create(std::move(expression));

			lhs = &syntax;
			type = getEqualityType(token);
		}

		return lhs;
	}
}
