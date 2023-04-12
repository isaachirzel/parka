#include "parka/syntax/RelationalExpressionSyntax.hpp"
#include "parka/syntax/ShiftExpressionSyntax.hpp"
#include "parka/repository/SyntaxRepository.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	Optional<RelationalType> parseRelationalType(Token& token)
	{
		switch (token.type())
		{
			case TokenType::GreaterThan:
				return RelationalType::GreaterThan;

			case TokenType::LessThan:
				return RelationalType::LessThan;

			case TokenType::GreaterThanOrEqualTo:
				return RelationalType::GreaterThanOrEqualTo;

			case TokenType::LessThanOrEqualTo:
				return RelationalType::LessThanOrEqualTo;

			default:
				return {};
		}
	}

	Optional<ExpressionSyntaxId> RelationalExpressionSyntax::parse(Token& token)
	{
		auto lhs = ShiftExpressionSyntax::parse(token);

		if (!lhs)
			return {};

		auto type = parseRelationalType(token);

		while (type)
		{
			token.increment();

			auto rhs = ShiftExpressionSyntax::parse(token);

			if (!rhs)
				return {};

			auto expression = RelationalExpressionSyntax(*lhs, *rhs, *type);
			auto id = SyntaxRepository::add(std::move(expression));

			lhs = std::move(id);
			type = parseRelationalType(token);
		}

		return lhs;
	}
}
