#ifndef PARKA_AST_EXPRESSION_PRIMARY_HPP
#define PARKA_AST_EXPRESSION_PRIMARY_HPP

#include "parka/ast/expression/expression.hpp"

struct PrimaryExpression
{
	static Optional<ExpressionId> parse(Token& token);
};

#endif
