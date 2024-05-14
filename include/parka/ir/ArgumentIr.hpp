#ifndef PARKA_IR_ARGUMENT_IR_HPP
#define PARKA_IR_ARGUMENT_IR_HPP

#include "parka/ir/ConversionIr.hpp"
#include "parka/ir/ExpressionIr.hpp"

namespace parka::ir
{
	class ArgumentIr
	{
		ExpressionIr& _value;
		ConversionIr* _conversion;

	public:

		ArgumentIr(ExpressionIr& value, ConversionIr* conversion):
			_value(value),
			_conversion(conversion)
		{}
		ArgumentIr(ArgumentIr&&) = default;
		ArgumentIr(const ArgumentIr&) = delete;

		const auto& value() const { return _value; }
		const auto* conversion() const { return _conversion; }
	};
}

#endif
