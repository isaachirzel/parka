#include <warbler/ast/typename.h>

// standard headers
#include <stdlib.h>
#include <assert.h>

void typename_init(Typename *self)
{
	assert(self);

	self->text = NULL;
}

void typename_free(Typename *self)
{
	if (!self)
		return;

	free(self->text);
}

Error typename_parse(Typename *self, TokenIterator *iter)
{
	assert(self);
	assert(iter);

	typename_init(self);
	
	if (iter->token->type != TOKEN_IDENTIFIER)
		return ERROR_ARGUMENT;

	self->text = string_duplicate(&iter->token->text);

	if (!self->text)
		return ERROR_MEMORY;

	return ERROR_NONE;
}
