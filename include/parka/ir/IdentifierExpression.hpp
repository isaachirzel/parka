#ifndef PARKA_IR_IDENTIFIER_EXPRESSION_HPP
#define PARKA_IR_IDENTIFIER_EXPRESSION_HPP

#include "parka/ir/Expression.hpp"
#include "parka/ir/LValue.hpp"

namespace parka::ir
{
	class IdentifierExpressionIr: public ExpressionIr
	{
		LValue& _value;

	public:

		IdentifierExpressionIr(LValue& reference):
			ExpressionIr(ExpressionType::Identifier),
			_value(reference)
		{}
		IdentifierExpressionIr(IdentifierExpressionIr&&) = default;
		IdentifierExpressionIr(const IdentifierExpressionIr&) = delete;

		const auto& value() const { return _value; }
		const Type& type() const { return _value.type(); }
	};
}

#endif
