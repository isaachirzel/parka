#include <warbler/ast/identifier.h>

// standard headers
#include <stdlib.h>

Error identifier_parse(Identifier *out, TokenIterator *iter)
{	
	if (iter->token[0].type != TOKEN_IDENTIFIER)
		return ERROR_ARGUMENT;
	
	out->text = string_duplicate(&iter->token[0].string);

	if (!out->text)
		return ERROR_MEMORY;

	++iter->token;

	return ERROR_NONE;
}

void identifier_free(Identifier *identifier)
{
	free(identifier->text);
}
