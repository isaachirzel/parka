#ifndef WARBLER_AST_EXPRESSION_CONDITIONAL_H
#define WARBLER_AST_EXPRESSION_CONDITIONAL_H

// local headers
#include <warbler/ast/expression/boolean/or.h>

struct Expression;

typedef enum ConditionalType
{
	CONDITIONAL_BINARY,
	CONDITIONAL_TERNARY
} ConditionalType;

typedef struct ConditionalExpression
{
	BooleanOrExpression *lhs;
	ConditionalType type;
} ConditionalExpression;

void conditional_expression_init(ConditionalExpression *expr);
void conditional_expression_free(ConditionalExpression *exor);
Error conditional_expression_parse(ConditionalExpression *out, TokenIterator *iter);

#endif
