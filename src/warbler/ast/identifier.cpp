#include <warbler/ast/identifier.hpp>

// local headers
#include <warbler/print.hpp>

// standard headers
#include <cstdlib>

namespace warbler
{
void identifier_init(Identifier *self)
{
	assert(self);
	
	self->text = NULL;
}

void identifier_free(Identifier *self)
{
	if (!self)
		return;

	free(self->text);
}

Error identifier_parse(Identifier *self, TokenIterator& iter)
{
	assert(self);
	

	identifier_init(self);

	if (iter->type != TOKEN_IDENTIFIER)
	{
		errortf(*iter, "expected identifier but got: %t", iter);
		return ERROR_ARGUMENT;
	}

	self->text = string_duplicate(&iter->text);

	if (!self->text)
		return ERROR_MEMORY;
		
	++iter;

	return ERROR_NONE;
}

void identifier_print_tree(Identifier *self, unsigned depth)
{
	assert(self);

	print_branch(depth);
	puts(self->text);
}
}