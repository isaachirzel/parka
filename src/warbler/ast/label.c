#include <warbler/ast/label.h>

void label_init(Label *label)
{
	identifier_init(&label->identifier);
}

void label_free(Label *label)
{
	identifier_free(&label->identifier);
}

Error label_parse(Label *label, TokenIterator *iter)
{
	if (iter->token[0].type != TOKEN_IDENTIFIER || iter->token[1].type != TOKEN_COLON)
		return ERROR_ARGUMENT;
	
	Error error;

	if ((error = identifier_parse(&label->identifier, iter)))
		return error;

	if (iter->token->type != TOKEN_COLON)
	{
		label_free(label);
		print_error("expected ':' after label but got: ");
		string_println(&iter->token->string);
		return ERROR_ARGUMENT;
	}

	++iter->token;
	
	return ERROR_NONE;
}
