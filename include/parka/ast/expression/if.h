#ifndef PARKA_AST_EXPRESSION_IF_H
#define PARKA_AST_EXPRESSION_IF_H

#include "parka/ast/expression/expression.h"

typedef enum IfType
{
	IF_THEN,
	IF_THEN_ELSE,
	IF_THEN_ELSE_IF
} IfType;

typedef struct IfExpression
{
	Expression condition;
	struct Statement *thenCase;

	union
	{
		struct Statement *elseCase;
		struct IfExpression *elseIf;
	};

	IfType type;
} IfExpression;

void ifExpressionFree(IfExpression *node);

#endif
