#ifndef PARKA_IR_IDENTIFIER_EXPRESSION_HPP
#define PARKA_IR_IDENTIFIER_EXPRESSION_HPP

#include "parka/ir/Expression.hpp"

namespace parka::ir
{
	class IdentifierExpressionIr: public ExpressionIr
	{
		Resolution& _entity;
		ValueType _valueType;

	public:

		IdentifierExpressionIr(Resolution& entity, ValueType&& valueType):
		ExpressionIr(ExpressionType::Identifier),
		_entity(entity),
		_valueType(std::move(valueType))
		{}
		IdentifierExpressionIr(IdentifierExpressionIr&&) = default;
		IdentifierExpressionIr(const IdentifierExpressionIr&) = delete;

		const auto& entity() const { return _entity; }
		const ValueType& valueType() const { return _valueType; }
	};
}

#endif
