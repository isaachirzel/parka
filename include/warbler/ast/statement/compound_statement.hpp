#ifndef WARBLER_AST_Compound_STATEMENT_HPP
#define WARBLER_AST_Compound_STATEMENT_HPP

// local headers
#include <warbler/result.hpp>
#include <warbler/token.hpp>
namespace warbler
{
struct Statement;

typedef struct CompoundStatement
{
	struct Statement *statements;
	size_t statement_count;
} CompoundStatement;

void compound_statement_init(CompoundStatement *compound);
void compound_statement_free(CompoundStatement *compound);
Error compound_statement_parse(CompoundStatement *compound, TokenIterator& iter);
}
#endif
