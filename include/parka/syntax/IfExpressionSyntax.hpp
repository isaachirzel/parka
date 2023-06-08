#ifndef PARKA_SYNTAX_IF_EXPRESSION_SYNTAX_HPP
#define PARKA_SYNTAX_IF_EXPRESSION_SYNTAX_HPP

#include "parka/syntax/ExpressionSyntax.hpp"

// TODO: Consider merging this with conditional expression

namespace parka
{
	class IfExpressionSyntax : public ExpressionSyntax
	{
		ExpressionType expressionType() const { return ExpressionType::If; }
	};
}

#endif
