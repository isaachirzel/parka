#include <warbler/ast/identifier.h>

// local headers
#include <warbler/print.h>

// standard headers
#include <stdlib.h>

void identifier_init(Identifier *self)
{
	self->text = NULL;
}

void identifier_free(Identifier *self)
{
	free(self->text);
}

static inline Error try_identifier_parse(Identifier *self, TokenIterator *iter)
{
	if (iter->token->type != TOKEN_IDENTIFIER)
		return ERROR_ARGUMENT;

	self->text = string_duplicate(&iter->token->text);

	if (!self->text)
		return ERROR_MEMORY;
		
	++iter->token;

	return ERROR_NONE;
}

Error identifier_parse(Identifier *self, TokenIterator *iter)
{	
	assert(self != NULL);
	assert(iter != NULL);

	identifier_init(self);

	Error error = try_identifier_parse(self, iter);

	if (error)
		identifier_free(self);

	debugf("parsed identifier: %s\n", self->text);

	return error;
}

void identifier_print_tree(Identifier *self, unsigned depth)
{
	print_branch(depth);
	puts(self->text);
}
