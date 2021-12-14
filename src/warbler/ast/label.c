#include <warbler/ast/label.h>

Error label_parse(Label *out, TokenIterator *iter)
{
	if (iter->token[0].type != TOKEN_IDENTIFIER || iter->token[1].type != TOKEN_COLON)
		return ERROR_ARGUMENT;
	
	Identifier identifier;
	Error error = identifier_parse(&identifier, iter);

	if (error)
	{
		identifier_free(&identifier);
		return error;
	}

	++iter->token;

	out->identifier = malloc(sizeof(Identifier));

	if (!out->identifier)
	{
		identifier_free(&identifier);
		return ERROR_MEMORY;
	}

	*out->identifier = identifier;
	
	return ERROR_NONE;
}

void label_free(Label *label)
{
	free(label->identifier);
}
