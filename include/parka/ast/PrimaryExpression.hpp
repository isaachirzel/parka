#ifndef PARKA_SYNTAX_EXPRESSION_PRIMARY_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_PRIMARY_SYNTAX_HPP

#include "parka/ast/Expression.hpp"

namespace parka::PrimaryExpressionSyntax
{
	ExpressionSyntax *parse(Token& token);
}

#endif
