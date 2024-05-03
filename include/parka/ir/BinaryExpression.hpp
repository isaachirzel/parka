#ifndef PARKA_IR_BINARY_EXPRESSION_HPP
#define PARKA_IR_BINARY_EXPRESSION_HPP

#include "parka/ir/Expression.hpp"
#include "parka/enum/BinaryExpressionType.hpp"
#include "parka/ir/Operator.hpp"

namespace parka::ir
{
	class BinaryExpressionIr: public ExpressionIr
	{
		ExpressionIr& _lhs;
		ExpressionIr& _rhs;
		OperatorIr& _op;

	public:

		BinaryExpressionIr(ExpressionIr& lhs, ExpressionIr& rhs, OperatorIr& op):
			ExpressionIr(ExpressionType::Binary),
			_lhs(lhs),
			_rhs(rhs),
			_op(op)
		{}

		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
		const auto& op() const { return _op; }
		const Type& type() const { return _op.returnType(); }
	};
}

#endif
