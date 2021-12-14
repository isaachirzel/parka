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

Error Compound_statement_parse(CompoundStatement *compound, TokenIterator *iter);
void compound_statement_free(CompoundStatement *compound);

#endif
