#ifndef PARKA_IR_ASSIGNMENT_EXPRESSION_HPP
#define PARKA_IR_ASSIGNMENT_EXPRESSION_HPP

#include "parka/enum/AssignmentType.hpp"
#include "parka/ir/Expression.hpp"

namespace parka::ir
{
	class AssignmentExpressionIr : public ExpressionIr
	{
		ExpressionIr& _lhs;
		ExpressionIr& _rhs;
		AssignmentType _assignmentType;

	public:

		AssignmentExpressionIr(ExpressionIr& lhs, ExpressionIr& rhs, AssignmentType assignmentType) :
		_lhs(lhs),
		_rhs(rhs),
		_assignmentType(assignmentType)
		{}
		AssignmentExpressionIr(AssignmentExpressionIr&&) = default;
		AssignmentExpressionIr(const AssignmentExpressionIr&) = delete;

		ExpressionType expressionType() const { return ExpressionType::Assignment; }
		const ValueType& valueType() const { return ValueType::voidType; }
		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
		const auto& assignmentType() const { return _assignmentType; }
	};
}

#endif
