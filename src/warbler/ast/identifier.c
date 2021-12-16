#include <warbler/ast/identifier.h>

// standard headers
#include <stdlib.h>

void identifier_init(Identifier *identifier)
{
	identifier->text = NULL;
}

void identifier_free(Identifier *identifier)
{
	free(identifier->text);
}

static inline Error try_identifier_parse(Identifier *identifier, TokenIterator *iter)
{
	if (iter->token->type != TOKEN_IDENTIFIER)
		return ERROR_ARGUMENT;

	out->text = string_duplicate(&iter->token->string);

	if (!out->text)
		return ERROR_MEMORY;

	return ERROR_NONE;
}

Error identifier_parse(Identifier *identifier, TokenIterator *iter)
{	
	assert(identifier != NULL);
	assert(iter != NULL);

	identifier_init(identifier);

	Error error = try_identifier_parse(identifier, iter);

	if (error)
		identifier_free(identifier);

	return error;
}
