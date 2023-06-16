#ifndef PARKA_AST_EXPRESSION_PRIMARY_HPP
#define PARKA_AST_EXPRESSION_PRIMARY_HPP

#include "parka/ast/Expression.hpp"

namespace parka::PrimaryExpressionAst
{
	ExpressionAst *parse(Token& token);
}

#endif
