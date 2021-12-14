#ifndef WARBLER_AST_EXPRESSION_LOGICAL_AND_H
#define WARBLER_AST_EXPRESSION_LOGICAL_AND_H

// local headers
#include <warbler/ast/expression/bitwise_or.h>

typedef struct BooleanAndExpression
{
	BitwiseOrExpression *conditions;
	size_t condition_count;
} BooleanAndExpression;

#endif
