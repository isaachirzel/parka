#ifndef PARKA_IR_INTEGER_LITERAL_HPP
#define PARKA_IR_INTEGER_LITERAL_HPP

#include "parka/ir/Expression.hpp"

namespace parka::ir
{
	class IntegerLiteralIr: public ExpressionIr
	{
		u64 _value;
		Type _type;

	public:

		IntegerLiteralIr(u64 value, Type&& type):
		ExpressionIr(ExpressionType::IntegerLiteral),
		_value(value),
		_type(std::move(type))
		{}
		IntegerLiteralIr(IntegerLiteralIr&&) = default;
		IntegerLiteralIr(const IntegerLiteralIr&) = delete;
		
		// TODO: Actually check size of literal
		const auto&  value() const { return _value; }
		const Type& type() const { return _type; }
	};
}

#endif
