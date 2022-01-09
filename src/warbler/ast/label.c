#include <warbler/ast/label.h>

// local headers
#include <warbler/print.h>

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

Error label_parse(Label *self, TokenIterator *iter)
{
	if (iter->token[0].type != TOKEN_IDENTIFIER || iter->token[1].type != TOKEN_COLON)
		return ERROR_ARGUMENT;
	
	try(identifier_parse(&self->identifier, iter));

	if (iter->token->type != TOKEN_COLON)
	{
		errortf(iter->token, "expected ':' after label but got: %t", iter->token);
		return ERROR_ARGUMENT;
	}

	++iter->token;
	
	return ERROR_NONE;
}

void label_print_tree(Label *self, unsigned depth)
{
	assert(self);

	identifier_print_tree(&self->identifier, depth);
}
