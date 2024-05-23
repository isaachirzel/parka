#ifndef PARKA_IR_CAST_EXPRESSION_IR_HPP
#define PARKA_IR_CAST_EXPRESSION_IR_HPP

#include "parka/ir/ConversionIr.hpp"
#include "parka/ir/ExpressionIr.hpp"

namespace parka::ir
{
	class CastExpressionIr: public ExpressionIr
	{
		ExpressionIr& _expression;
		ConversionIr& _conversion;

	public:

		CastExpressionIr(ExpressionIr& expression, ConversionIr& conversion):
			ExpressionIr(ExpressionType::Cast),
			_expression(expression),
			_conversion(conversion)
		{}
		CastExpressionIr(CastExpressionIr&&) = default;
		CastExpressionIr(const CastExpressionIr&) = delete;

		const TypeIr& type() const { return _conversion.to(); }
		const auto& expression() const { return _expression; }
		const auto& conversion() const { return _conversion; }
	};
}

#endif
