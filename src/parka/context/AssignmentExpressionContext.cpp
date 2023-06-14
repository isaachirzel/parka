#include "parka/context/AssignmentExpressionContext.hpp"

namespace parka
{
	AssignmentExpressionContext::AssignmentExpressionContext(ExpressionContext& lhs, ExpressionContext& rhs, AssignmentType assignmentType) :
	_lhs(lhs),
	_rhs(rhs),
	_assignmentType(assignmentType)
	{}
}
