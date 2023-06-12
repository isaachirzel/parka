#include "parka/context/AdditiveExpressionContext.hpp"

namespace parka
{
	AdditiveExpressionContext::AdditiveExpressionContext(ExpressionContext& lhs, ExpressionContext& rhs, AdditiveType type) :
	_lhs(lhs),
	_rhs(rhs),
	_type(type)
	{}
}
