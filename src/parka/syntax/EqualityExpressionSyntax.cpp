#include "parka/syntax/EqualityExpressionSyntax.hpp"
#include "parka/syntax/RelationalExpressionSyntax.hpp"
#include "parka/repository/SyntaxRepository.hpp"
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

	Optional<ExpressionSyntaxId> EqualityExpressionSyntax::parse(Token& token)
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
			auto id = SyntaxRepository::add(std::move(expression));

			lhs = std::move(id);
			type = getEqualityType(token);
		}

		return lhs;
	}
}
