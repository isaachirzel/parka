#include <warbler/ast/typename.h>

// standard headers
#include <stdlib.h>
#include <assert.h>

void typename_init(Typename *typename)
{
	typename->text = NULL;
}

void typename_free(Typename *typename)
{
	free(typename->text);
}

static inline Error try_typename_parse(Typename *typename, TokenIterator *iter)
{
	if (iter->token->type != TOKEN_IDENTIFIER)
		return ERROR_ARGUMENT;

	typename->text = string_duplicate(&iter->token->string);

	if (!typename->text)
		return ERROR_MEMORY;

	return ERROR_NONE;
}

Error typename_parse(Typename *typename, TokenIterator *iter)
{
	assert(typename != NULL);
	assert(iter != NULL);

	typename_init(typname);

	Error error = try_typename_parse(typename, iter);

	if (error)
		typename_free(typename);
		
	return error;
}

