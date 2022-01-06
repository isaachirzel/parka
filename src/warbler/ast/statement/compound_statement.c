#include <warbler/ast/statement/compound_statement.h>

// standard headers
#include <assert.h>

void compound_statement_init(CompoundStatement *compound)
{
	compound->statements = NULL;
	compound->statement_count = 0;
}

void compound_statement_free(CompoundStatement *compound)
{
	compound_statement_free(compound);
}

Error compound_statement_parse(CompoundStatement *compound, TokenIterator *iter)
{
	assert(compound != NULL);
	assert(iter != NULL);

	return not_implemented_error();
}
