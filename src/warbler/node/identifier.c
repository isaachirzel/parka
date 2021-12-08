#include <warbler/node/identifier.h>

// standard library
#include <assert.h>
#include <stdlib.h>

Error identifier_parse(Identifier **out, const Token **tokens)
{
	assert(out != NULL);
	assert(tokens != NULL);
	
	if (tokens[0]->type != TOKEN_IDENTIFIER)
		return ERROR_ARGUMENT;

	Identifier *identifier = malloc(sizeof(Identifier));

	if (!identifier)
		return ERROR_MEMORY;

	identifier->string = tokens[0]->string;

	*tokens += 1;
	*out = identifier;

	return ERROR_NONE;
}
