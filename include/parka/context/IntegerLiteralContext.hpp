#ifndef PARKA_CONTEXT_INTEGER_LITERAL_CONTEXT_HPP
#define PARKA_CONTEXT_INTEGER_LITERAL_CONTEXT_HPP

#include "parka/context/ExpressionContext.hpp"

namespace parka
{
	class IntegerLiteralContext : public ExpressionContext
	{
		u64 _value;
		u32 _bytes;
		ValueType _valueType;

	public:

		IntegerLiteralContext(u64 value, u32 bytes, ValueType&& valueType);
		IntegerLiteralContext(IntegerLiteralContext&&) = default;
		IntegerLiteralContext(const IntegerLiteralContext&) = delete;
		
		ExpressionType expressionType() const { return ExpressionType::IntegerLiteral; }
		// TODO: Actually check size of literal
		const ValueType& valueType() const { return ValueType::i32Type; }
	};
}

#endif
