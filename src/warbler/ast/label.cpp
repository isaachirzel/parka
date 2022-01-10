#include <warbler/ast/label.hpp>

// local headers
#include <warbler/print.hpp>

namespace warbler
{
void label_init(Label *self)
{
	assert(self);

	identifier_init(&self->identifier);
}

void label_free(Label *self)
{
	if (!self)
		return;
		
	identifier_free(&self->identifier);
}

Error label_parse(Label *self, TokenIterator& iter)
{
	if (iter[0].type != TOKEN_IDENTIFIER || iter[1].type != TOKEN_COLON)
		return ERROR_ARGUMENT;
	
	try(identifier_parse(&self->identifier, iter));

	if (iter->type != TOKEN_COLON)
	{
		errortf(*iter, "expected ':' after label but got: %t", iter);
		return ERROR_ARGUMENT;
	}

	++iter;
	
	return ERROR_NONE;
}

void label_print_tree(Label *self, unsigned depth)
{
	assert(self);

	identifier_print_tree(&self->identifier, depth);
}
}