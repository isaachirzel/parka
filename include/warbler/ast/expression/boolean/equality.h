#ifndef WARBLER_AST_EXPRESSION_BOOLEAN_EQUALITY_H
#define WARBLER_AST_EXPRESSION_BOOLEAN_EQUALITY_H

// local headers
#include <warbler/ast/expression/boolean/comparison.h>

typedef struct EqualityExpression
{
	ComparisonExpression conditions;
	size_t condition_count;
} EqualityExpression;

#endif
