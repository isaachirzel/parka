#ifndef PARKA_IR_INTEGER_LITERAL_HPP
#define PARKA_IR_INTEGER_LITERAL_HPP

#include "parka/ir/Expression.hpp"

namespace parka::ir
{
	class IntegerLiteralIr : public ExpressionIr
	{
		u64 _value;
		ValueType _valueType;

	public:

		IntegerLiteralIr(u64 value, ValueType&& valueType) :
		ExpressionIr(ExpressionType::IntegerLiteral),
		_value(value),
		_valueType(std::move(valueType))
		{}
		IntegerLiteralIr(IntegerLiteralIr&&) = default;
		IntegerLiteralIr(const IntegerLiteralIr&) = delete;
		
		// TODO: Actually check size of literal
		const ValueType& valueType() const { return ValueType::i32Type; }

		friend class IntegerLiteralAst;
	};
}

#endif
