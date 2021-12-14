#include <warbler/ast/typename.h>

// standard headers
#include <stdlib.h>

Error typename_parse(Typename *out, TokenIterator *iter)
{
	if (iter->token->type != TOKEN_IDENTIFIER)
		return ERROR_ARGUMENT;

	out->text = string_duplicate(&iter->token->string);

	if (!out)
		return ERROR_MEMORY;
	
	++iter->token;

	return ERROR_NONE;
}

void typename_free(Typename *typename)
{
	free(typename->text);
}
