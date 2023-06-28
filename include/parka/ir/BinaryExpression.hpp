#ifndef PARKA_IR_BINARY_EXPRESSION_HPP
#define PARKA_IR_BINARY_EXPRESSION_HPP

#include "parka/ir/Expression.hpp"
#include "parka/enum/BinaryExpressionType.hpp"

namespace parka::ir
{
	class BinaryExpressionIr: public ExpressionIr
	{
		ExpressionIr& _lhs;
		ExpressionIr& _rhs;
		ValueType _valueType;
		BinaryExpressionType _binaryExpressionType;

	public:

		BinaryExpressionIr(ExpressionIr& lhs, ExpressionIr& rhs, BinaryExpressionType binaryExpressionType, ValueType&& valueType):
		ExpressionIr(ExpressionType::Binary),
		_lhs(lhs),
		_rhs(rhs),
		_valueType(valueType),
		_binaryExpressionType(binaryExpressionType)
		{}

		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
		const ValueType& valueType() const { return _valueType; }
		const auto& binaryExpressionType() const { return _binaryExpressionType; }
	};
}

#endif
