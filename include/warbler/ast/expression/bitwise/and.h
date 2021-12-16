#ifndef WARBLER_AST_EXPRESSION_BITWISE_AND_H
#define WARBLER_AST_EXPRESSION_BITWISE_AND_H

// local headers
#include <warbler/ast/expression/boolean/equality.h>

typedef struct BitwiseAndExpression
{
	EqualityExpression *conditions;
	size_t condition_count;
} BitwiseAndExpression;

#endif
