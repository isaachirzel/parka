#include <warbler/ast/identifier.h>

// local headers
#include <warbler/print.h>

// standard headers
#include <stdlib.h>

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

Error identifier_parse(Identifier *self, TokenIterator *iter)
{
	assert(self);
	assert(iter);

	identifier_init(self);

	debugf("trying parameter parse of token type: %d\n", iter->token->type);

	if (iter->token->type != TOKEN_IDENTIFIER)
	{
		errort("expected identifier but got", iter->token);
		return ERROR_ARGUMENT;
	}

	self->text = string_duplicate(&iter->token->text);

	if (!self->text)
		return ERROR_MEMORY;
		
	++iter->token;

	return ERROR_NONE;
}

void identifier_print_tree(Identifier *self, unsigned depth)
{
	assert(self);

	print_branch(depth);
	puts(self->text);
}
