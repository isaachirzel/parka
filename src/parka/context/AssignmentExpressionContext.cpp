#include "parka/context/AssignmentExpressionContext.hpp"

namespace parka
{
	AssignmentExpressionContext::AssignmentExpressionContext(ExpressionContext& lhs, ExpressionContext& rhs, AssignmentType type) :
	_lhs(lhs),
	_rhs(rhs),
	_type(type)
	{}
}
