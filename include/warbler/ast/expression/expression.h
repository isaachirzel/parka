#ifndef WARBLER_AST_EXPRESSION_H
#define WARBLER_AST_EXPRESSION_H

#include <warbler/ast/expression/assignment.h>

typedef struct
{
	Assignment *assignment;
} Expression;

Error expression_parse(Expression *out, TokenIterator *iter);
void expression_free(Expression *expression);

#endif
