#include "parka/context/AdditiveExpressionContext.hpp"

namespace parka
{
	AdditiveExpressionContext::AdditiveExpressionContext(ExpressionContext& lhs, ExpressionContext& rhs, AdditiveType additiveType, ValueType&& valueType) :
	_lhs(lhs),
	_rhs(rhs),
	_additiveType(additiveType),
	_valueType(std::move(valueType))
	{}
}
