#ifndef WARBLER_AST_Compound_STATEMENT_H
#define WARBLER_AST_Compound_STATEMENT_H

// local headers
#include <warbler/error.h>
#include <warbler/token.h>

struct Statement;

typedef struct CompoundStatement
{
	struct Statement *statements;
	size_t statement_count;
} CompoundStatement;

void compound_statement_init(CompoundStatement *compound);
void compound_statement_free(CompoundStatement *compound);
Error compound_statement_parse(CompoundStatement *compound, TokenIterator *iter);

#endif
