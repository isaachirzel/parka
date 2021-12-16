#ifndef WARBLER_AST_EXPRESSION_BOOLEAN_AND_H
#define WARBLER_AST_EXPRESSION_BOOLEAN_AND_H

// local headers
#include <warbler/ast/expression/bitwise/or.h>

typedef struct BooleanAndExpression
{
	BitwiseOrExpression *lhs;
	BitwiseOrExpression *rhs;
	size_t rhs_count;
} BooleanAndExpression;


#endif
