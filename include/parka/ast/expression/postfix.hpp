#ifndef PARKA_AST_EXPRESSION_POSTFIX_HPP
#define PARKA_AST_EXPRESSION_POSTFIX_HPP

#include "parka/ast/expression/expression.hpp"

struct PostfixExpression
{
	static Optional<Box<Expression>> parse(Token& token);
};

#endif
