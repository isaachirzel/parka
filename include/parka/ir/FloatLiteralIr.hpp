#ifndef PARKA_IR_FLOAT_LITERAL_HPP
#define PARKA_IR_FLOAT_LITERAL_HPP

#include "parka/ir/ExpressionIr.hpp"
#include "parka/ir/FloatPrimitiveIr.hpp"
#include "parka/ir/TypeIr.hpp"
#include "parka/util/Common.hpp"

namespace parka::ir
{
	class FloatLiteralIr: public ExpressionIr
	{
		f64 _value;

	public:

		FloatLiteralIr(f64 value);
		FloatLiteralIr(FloatLiteralIr&&) = default;
		FloatLiteralIr(const FloatLiteralIr&) = delete;

		const auto& value() const { return _value; }
		const TypeIr& type() const { return FloatPrimitiveIr::floatPrimitive; }
	};
}

#endif
