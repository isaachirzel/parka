#ifndef WARBLER_AST_EXPRESSION_H
#define WARBLER_AST_EXPRESSION_H

#include <warbler/ast/expression/assignment.h>

typedef struct
{
	AssignmentExpression assignment;
} Expression;

void expression_init(Expression *expression);
void expression_free(Expression *expression);
Error expression_parse(Expression *out, TokenIterator *iter);

#endif
