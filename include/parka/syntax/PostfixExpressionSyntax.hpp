#ifndef PARKA_SYNTAX_EXPRESSION_POSTFIX_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_POSTFIX_SYNTAX_HPP

#include "parka/syntax/ExpressionSyntax.hpp"

namespace parka::PostfixExpressionSyntax
{
	ExpressionSyntax *parse(Token& token);
}

#endif
