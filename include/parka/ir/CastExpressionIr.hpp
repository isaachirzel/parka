#ifndef PARKA_IR_CAST_EXPRESSION_IR_HPP
#define PARKA_IR_CAST_EXPRESSION_IR_HPP

#include "parka/ir/ConversionIr.hpp"
#include "parka/ir/ExpressionIr.hpp"

namespace parka::ir
{
	class CastExpressionIr: public ExpressionIr
	{
		TypeIr _type;
		ExpressionIr& _expression;
		ConversionIr* _conversion;

	public:

		CastExpressionIr(TypeIr&& type, ExpressionIr& expression, ConversionIr* conversion):
			ExpressionIr(ExpressionType::Cast),
			_type(std::move(type)),
			_expression(expression),
			_conversion(conversion)
		{}
		CastExpressionIr(CastExpressionIr&&) = default;
		CastExpressionIr(const CastExpressionIr&) = delete;

		const TypeIr& type() const { return _type; }
		const auto& expression() const { return _expression; }
		const auto* conversion() const { return _conversion; }
	};
}

#endif
