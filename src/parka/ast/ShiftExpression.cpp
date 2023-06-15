#include "parka/ast/ShiftExpression.hpp"
#include "parka/log/Log.hpp"
#include "parka/ast/AdditiveExpression.hpp"

namespace parka
{
	static Optional<ShiftType> parseBitShiftType(Token& token)
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

	ExpressionSyntax *ShiftExpressionSyntax::parse(Token& token)
	{
		auto *lhs = AdditiveExpressionSyntax::parse(token);

		if (!lhs)
			return {};

		auto type = parseBitShiftType(token);

		while (type)
		{
			token.increment();

			auto rhs = AdditiveExpressionSyntax::parse(token);

			if (!rhs)
				return {};

			lhs = new ShiftExpressionSyntax(*lhs, *rhs, *type);
			type = parseBitShiftType(token);
		}

		return lhs;
	}

	ExpressionContext *ShiftExpressionSyntax::validate(SymbolTable&)
	{
		log::notImplemented(here());
	}
}