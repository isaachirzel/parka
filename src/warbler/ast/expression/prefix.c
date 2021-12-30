#include <warbler/ast/expression/prefix.h>

// local headers
#include <warbler/print.h>

Error prefix_parse(Prefix *self, TokenIterator *iter)
{
	assert(self != NULL);
	assert(iter != NULL);

	switch (iter->token->type)
	{
		case TOKEN_INCREMENT:
			self->type = PREFIX_INCREMENT;
			break;

		case TOKEN_DECREMENT:
			self->type = PREFIX_DECREMENT;
			break;

		case TOKEN_AMPERSAND:
			self->type = PREFIX_REFERENCE;
			break;

		case TOKEN_ASTERISK:
			self->type = PREFIX_DEREFERENCE;
			break;

		default:
			print_error("expected prefix but got: ");
			token_println(iter->token);
			return ERROR_ARGUMENT;
	}

	return ERROR_NONE;
}

void prefix_print_tree(Prefix *self, unsigned depth)
{
	print_branch(depth);

	switch (self->type)
	{
		case PREFIX_INCREMENT:
			puts("++");
			break;

		case PREFIX_DECREMENT:
			puts("--");
			break;

		case PREFIX_REFERENCE:
			puts("&");
			break;

		case PREFIX_DEREFERENCE:
			puts("*");
			break;
	}
}
