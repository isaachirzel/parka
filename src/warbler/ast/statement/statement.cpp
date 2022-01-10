#include <warbler/ast/statement/statement.hpp>

namespace warbler
{
	void statement_init(Statement *self)
	{
		self->type = STATEMENT_COMPOUND;
		compound_statement_init(&self->compound);
	}

	void statement_parse(Statement *self, TokenIterator& iter)
	{
	}

	void statement_print_tree(Statement *self)
	{
	}
}