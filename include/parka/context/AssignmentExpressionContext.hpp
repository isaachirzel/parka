#ifndef PARKA_CONTEXT_ASSIGNMENT_EXPRESSION_CONTEXT_HPP
#define PARKA_CONTEXT_ASSIGNMENT_EXPRESSION_CONTEXT_HPP

#include "parka/context/ExpressionContext.hpp"
#include "parka/enum/AssignmentType.hpp"

namespace parka
{
	class AssignmentExpressionContext : public ExpressionContext
	{
		ExpressionContext& _lhs;
		ExpressionContext& _rhs;
		AssignmentType _assignmentType;

	public:

		AssignmentExpressionContext(ExpressionContext& lhs, ExpressionContext& rhs, AssignmentType assignmentType);
		AssignmentExpressionContext(AssignmentExpressionContext&&) = default;
		AssignmentExpressionContext(const AssignmentExpressionContext&) = delete;

		ExpressionType expressionType() const { return ExpressionType::Assignment; }
		const ValueType& valueType() const { return ValueType::voidType; }
		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
		const auto& assignmentType() const { return _assignmentType; }
	};
}

#endif
