#include "parka/syntax/ShiftExpressionSyntax.hpp"
#include "parka/syntax/AdditiveExpressionSyntax.hpp"
#include "parka/repository/Storage.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	Optional<ShiftType> parseBitShiftType(Token& token)
	{
		switch (token.type())
		{
			case TokenType::LeftBitShift:
				return ShiftType::Left;

			case TokenType::RightBitShift:
				return ShiftType::Right;

			default:
				return {};
		}
	}

	Optional<ExpressionSyntaxId> ShiftExpressionSyntax::parse(Token& token)
	{
		auto lhs = AdditiveExpressionSyntax::parse(token);

		if (!lhs)
			return {};

		auto type = parseBitShiftType(token);

		while (type)
		{
			token.increment();

			auto rhs = AdditiveExpressionSyntax::parse(token);

			if (!rhs)
				return {};

			auto expression = ShiftExpressionSyntax(*lhs, *rhs, *type);
			auto id = Storage::add(std::move(expression));

			lhs = std::move(id);
			type = parseBitShiftType(token);
		}

		return lhs;
	}
}
