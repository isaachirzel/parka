#ifndef PARKA_IR_INTEGER_LITERAL_HPP
#define PARKA_IR_INTEGER_LITERAL_HPP

#include "parka/ir/ExpressionIr.hpp"

namespace parka::ir
{
	class IntegerLiteralIr: public ExpressionIr
	{
		i64 _value;
		usize _size;

	public:

		IntegerLiteralIr(u64 value);
		IntegerLiteralIr(IntegerLiteralIr&&) = default;
		IntegerLiteralIr(const IntegerLiteralIr&) = delete;
		
		const auto& value() const { return _value; }
		const auto& size() const { return _size; }
		const TypeIr& type() const { return TypeIr::integerType; }
	};
}

#endif
