#include "parka/ast/ShiftExpression.hpp"
#include "parka/log/Log.hpp"
#include "parka/ast/AdditiveExpression.hpp"

namespace parka::ast
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

	ExpressionAst *ShiftExpressionAst::parse(Token& token)
	{
		auto *lhs = AdditiveExpressionAst::parse(token);

		if (!lhs)
			return {};

		auto type = parseBitShiftType(token);

		while (type)
		{
			token.increment();

			auto rhs = AdditiveExpressionAst::parse(token);

			if (!rhs)
				return {};

			lhs = new ShiftExpressionAst(*lhs, *rhs, *type);
			type = parseBitShiftType(token);
		}

		return lhs;
	}

	ir::ExpressionIr *ShiftExpressionAst::validate(SymbolTable&)
	{
		log::notImplemented(here());
	}
}