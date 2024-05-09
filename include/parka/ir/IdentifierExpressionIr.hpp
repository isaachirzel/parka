#ifndef PARKA_IR_IDENTIFIER_EXPRESSION_HPP
#define PARKA_IR_IDENTIFIER_EXPRESSION_HPP

#include "parka/ir/ExpressionIr.hpp"
#include "parka/ir/LValueIr.hpp"

namespace parka::ir
{
	class IdentifierExpressionIr: public ExpressionIr
	{
		LValueIr& _value;

	public:

		IdentifierExpressionIr(LValueIr& reference):
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
