#ifndef PARKA_IR_CAST_EXPRESSION_IR_HPP
#define PARKA_IR_CAST_EXPRESSION_IR_HPP

#include "parka/ir/CastIr.hpp"
#include "parka/ir/ExpressionIr.hpp"

namespace parka::ir
{
	class CastExpressionIr: public ExpressionIr
	{
		ExpressionIr& _expression;
		CastIr& _cast;

	public:

		CastExpressionIr(ExpressionIr& expression, CastIr& cast):
			ExpressionIr(ExpressionType::Cast),
			_expression(expression),
			_cast(cast)
		{}
		CastExpressionIr(CastExpressionIr&&) = default;
		CastExpressionIr(const CastExpressionIr&) = delete;

		const TypeIr& type() const { return _cast.to(); }
		const auto& expression() const { return _expression; }
		const auto& cast() const { return _cast; }
	};
}

#endif
