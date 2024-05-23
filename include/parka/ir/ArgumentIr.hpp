#ifndef PARKA_IR_ARGUMENT_IR_HPP
#define PARKA_IR_ARGUMENT_IR_HPP

#include "parka/ir/ExpressionIr.hpp"

namespace parka::ir
{
	class ArgumentIr
	{
		ExpressionIr& _value;

	public:

		ArgumentIr(ExpressionIr& value):
			_value(value)
		{}
		ArgumentIr(ArgumentIr&&) = default;
		ArgumentIr(const ArgumentIr&) = delete;

		const auto& value() const { return _value; }
	};
}

#endif
