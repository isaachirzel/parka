#include "parka/syntax/BitwiseXorExpressionSyntax.hpp"
#include "parka/syntax/BitwiseAndExpressionSyntax.hpp"

namespace parka
{
	BitwiseXorExpressionSyntax::BitwiseXorExpressionSyntax(ExpressionSyntax& lhs, ExpressionSyntax& rhs) :
	_lhs(lhs),
	_rhs(rhs)
	{}
}
