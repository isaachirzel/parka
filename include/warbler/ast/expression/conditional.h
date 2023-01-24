#ifndef WARBLER_AST_EXPRESSION_CONDITIONAL_H
#define WARBLER_AST_EXPRESSION_CONDITIONAL_H

#include "warbler/ast/expression/expression.h"

typedef struct ConditionalRhs
{
	Expression trueCase;
	Expression falseCase;
} ConditionalRhs;

typedef struct ConditionalExpression
{
	Expression expression;
	ConditionalRhs rhs;
	bool hasRhs;
} ConditionalExpression;

bool parseConditionalExpression(Expression *out, Token *token);
void conditionalExpressionFree(ConditionalExpression *node);

#endif
