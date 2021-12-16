#ifndef WARBLER_AST_EXPRESSION_ARITHMETIC_ADDITIVE_H
#define WARBLER_AST_EXPRESSION_ARITHMETIC_ADDITIVE_H

#include <warbler/ast/expression/arithmetic/multiplicative.h>

typedef enum AdditiveType
{
	ADDITIVE_ADD,
	ADDITIVE_SUBTRACT
} AdditiveType;

typedef struct AdditiveRhs
{
	MultiplicativeExpression *expr;
	AdditiveType type;
} AdditiveRhs;

typedef struct AdditiveExpression
{
	MultiplicativeExpression *lhs;
	AdditiveRhs *rhs;
	size_t rhs_count;
} AdditiveExpression;

#endif
