#ifndef WARBLER_AST_EXPRESSION_H
#define WARBLER_AST_EXPRESSION_H

#include <warbler/ast/expression/assignment.h>

typedef struct Expression
{
	AssignmentExpression assignment;
} Expression;

void expression_init(Expression *out);
void expression_free(Expression *out);
Error expression_parse(Expression *out, TokenIterator *iter);

#endif
