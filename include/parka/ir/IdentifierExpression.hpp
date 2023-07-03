#ifndef PARKA_IR_IDENTIFIER_EXPRESSION_HPP
#define PARKA_IR_IDENTIFIER_EXPRESSION_HPP

#include "parka/ir/Expression.hpp"
#include "parka/symbol/Resolution.hpp"

namespace parka::ir
{
	class IdentifierExpressionIr: public ExpressionIr
	{
		Value& _value;

	public:

		IdentifierExpressionIr(Value& value):
		ExpressionIr(ExpressionType::Identifier),
		_value(value)
		{}
		IdentifierExpressionIr(IdentifierExpressionIr&&) = default;
		IdentifierExpressionIr(const IdentifierExpressionIr&) = delete;

		const auto& value() const { return _value; }
		const Type& valueType() const { return _value.valueType(); }
	};
}

#endif
