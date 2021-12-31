#include <warbler/ast/label.h>

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
	
	Error error;

	if ((error = identifier_parse(&self->identifier, iter)))
		return error;

	if (iter->token->type != TOKEN_COLON)
	{
		label_free(self);
		print_error("expected ':' after label but got: ");
		token_print(iter->token);
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
