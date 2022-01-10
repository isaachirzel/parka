#include <warbler/ast/statement/compound_statement.hpp>

// standard headers
#include <cassert>

namespace warbler
{
void compound_statement_init(CompoundStatement *compound)
{
	compound->statements = NULL;
	compound->statement_count = 0;
}

void compound_statement_free(CompoundStatement *compound)
{
	compound_statement_free(compound);
}

Error compound_statement_parse(CompoundStatement *compound, TokenIterator& iter)
{
	assert(compound != NULL);
	

	return not_implemented_error();
}
}
