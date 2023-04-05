#ifndef PARKA_AST_EXPRESSION_POSTFIX_HPP
#define PARKA_AST_EXPRESSION_POSTFIX_HPP

#include "parka/ast/expression.hpp"

struct PostfixExpression
{
	static Optional<ExpressionId> parse(Token& token);
};

#endif
