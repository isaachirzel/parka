#ifndef PARKA_IR_FLOAT_LITERAL_HPP
#define PARKA_IR_FLOAT_LITERAL_HPP

#include "parka/enum/ExpressionType.hpp"
#include "parka/ir/Expression.hpp"
#include "parka/ir/Type.hpp"
#include "parka/util/Common.hpp"

namespace parka::ir
{
	class FloatLiteralIr: public ExpressionIr
	{
		f64 _value;
		Type _type;

	public:

		FloatLiteralIr(f64 value, Type&& type):
		ExpressionIr(ExpressionType::FloatLiteral),
		_value(value),
		_type(std::move(type))
		{}
		FloatLiteralIr(FloatLiteralIr&&) = default;
		FloatLiteralIr(const FloatLiteralIr&) = delete;

		const auto& value() const { return _value; }
		const Type& type() const { return _type; }
	};
}

#endif
