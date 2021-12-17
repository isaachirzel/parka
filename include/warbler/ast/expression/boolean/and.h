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

void boolean_and_expression_init(BooleanAndExpression *and);
void boolean_and_expression_free(BooleanAndExpression *and);
Error boolean_and_expression_parse(BooleanAndExpression *and, TokenIterator *iter);

#endif
