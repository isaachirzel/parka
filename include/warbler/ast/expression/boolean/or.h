#ifndef WARBLER_AST_EXPRESSION_BOOLEAN_OR_H
#define WARBLER_AST_EXPRESSION_BOOLEAN_OR_H

// local headers
#include <warbler/ast/expression/boolean/and.h>

typedef struct BooleanOrExpression
{
	BooleanAndExpression lhs;
	BooleanAndExpression *rhs;
	size_t rhs_count;
} BooleanOrExpression;

void boolean_or_expression_init(BooleanOrExpression *out);
void boolean_or_expression_free(BooleanOrExpression *out);
Error boolean_or_expression_parse(BooleanOrExpression *out, TokenIterator *iter);

#endif
