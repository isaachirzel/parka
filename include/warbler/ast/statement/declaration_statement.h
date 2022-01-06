#ifndef WARBLER_AST_DECLARATION_STATEMENT_H
#define WARBLER_AST_DECLARATION_STATEMENT_H

// local headers
#include <warbler/ast/typename.h>
#include <warbler/ast/identifier.h>
#include <warbler/ast/expression.h>

typedef struct DeclarationStatement
{
	Typename *typename;
	Identifier *identifier;
	Expression *expression;
} DeclarationStatement;

Error declaration_statement_parse(DeclarationStatement *declaration, TokenIterator *iter);
void declaration_statement_free(DeclarationStatement *declaration);

#endif
