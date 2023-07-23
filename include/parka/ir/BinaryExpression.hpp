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
		Type _type;
		BinaryExpressionType _binaryExpressionType;

	public:

		BinaryExpressionIr(ExpressionIr& lhs, ExpressionIr& rhs, BinaryExpressionType binaryExpressionType, Type&& Type):
		ExpressionIr(ExpressionType::Binary),
		_lhs(lhs),
		_rhs(rhs),
		_type(Type),
		_binaryExpressionType(binaryExpressionType)
		{}

		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
		const Type& type() const { return _type; }
		const auto& binaryExpressionType() const { return _binaryExpressionType; }
	};
}

#endif
