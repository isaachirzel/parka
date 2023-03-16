#ifndef PARKA_AST_EXPRESSION_RELATIONAL_H
#define PARKA_AST_EXPRESSION_RELATIONAL_H

#include "parka/ast/expression/expression.h"

typedef enum RelationalType
{
	RELATIONAL_GREATER_THAN,
	RELATIONAL_LESS_THAN,
	RELATIONAL_GREATER_THAN_OR_EQUAL_TO,
	RELATIONAL_LESS_THAN_OR_EQUAL_TO
} RelationalType;

typedef struct RelationalRhs
{
	Expression expr;
	RelationalType type;
} RelationalRhs;

typedef struct RelationalExpression
{
	Expression lhs;
	RelationalRhs* rhs;
	usize rhsCount;
} RelationalExpression;

bool parseRelationalExpression(Expression *out, Token *token);
void relationalExpressionFree(RelationalExpression *node);

#endif
