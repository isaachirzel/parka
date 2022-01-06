#ifndef WARBLER_AST_EXPRESSION_STATEMENT_H
#define WARBLER_AST_EXPRESSION_STATEMENT_H

// local headers
#include <warbler/token.h>
#include <warbler/error.h>

typedef struct ExpressionStatement
{
	
} ExpressionStatement;

Error Expression_statement_parse(ExpressionStatement *Expression, TokenIterator *iter);
void Expression_statement_free(ExpressionStatement *Expression);

#endif
