#ifndef WARBLER_AST_EXPRESSION_CONDITIONAL_H
#define WARBLER_AST_EXPRESSION_CONDITIONAL_H

// local headers
#include <warbler/ast/expression/boolean/or.h>

struct Expression;

typedef enum ConditionalType
{
	CONDITIONAL_NONE,
	CONDITIONAL_TERNARY
} ConditionalType;

typedef struct ConditionalExpression
{
	LogicalOrExpression *condition;
	struct Expression *true_result;
	struct ConditionalExpression *false_result;
	ConditionalType type;
} ConditionalExpression;

void conditional_expression_init(ConditionalExpression *conditional);
void conditional_expression_free(ConditionalExpression *conditional);
Error conditional_expression_parse(ConditionalExpression *conditional, TokenIterator *iter);

#endif
