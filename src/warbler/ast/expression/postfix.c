#include <warbler/ast/expression/postfix.h>

// local headers
#include <warbler/print.h>
#include <warbler/ast/expression/expression.h>

// standard headers
#include <assert.h>
#include <stdlib.h>


void postfix_init(Postfix *self)
{
	assert(self != NULL);

	*self = (Postfix)
	{
		.expression = NULL,
		.type = POSTFIX_INDEX
	};
}

void postfix_free(Postfix *self)
{
	assert(self != NULL);

	switch (self->type)
	{
		case POSTFIX_INDEX:
			if (self->expression)
				expression_free(self->expression);
			
			free(self->expression);
			break;

		case POSTFIX_CALL:
			parameter_list_free(&self->parameters);
			break;

		case POSTFIX_MEMBER:
			identifier_free(&self->identifier);
			break;
	}
}

static inline Error try_postfix_parse(Postfix *self, TokenIterator *iter)
{
	Error error;

	switch (iter->token->type)
	{
		case TOKEN_LBRACK:
			++iter->token;
			self->expression = malloc(sizeof(Expression));

			if (!self->expression)
				return ERROR_MEMORY;

			if ((error = expression_parse(self->expression, iter)))
				return error;
			break;

		case TOKEN_LPAREN:
			++iter->token;

			if ((error = parameter_list_parse(&self->parameters, iter)))
				return error;
			break;

		case TOKEN_DOT:
			++iter->token;

			if ((error = identifier_parse(&self->identifier, iter)))
				return error;
			break;

		default:
			print_error("expected postfix but got: ");
			token_println(iter->token);
			return ERROR_ARGUMENT;
	}

	return ERROR_NONE;
}

Error postfix_parse(Postfix *self, TokenIterator *iter)
{
	assert(self != NULL);
	assert(iter != NULL);

	postfix_init(self);

	Error error = try_postfix_parse(self, iter);

	if (error)
		postfix_free(self);

	return error;
}

void postfix_print_tree(Postfix *self, unsigned depth)
{
	assert(self != NULL);

	print_branch(depth);

	switch (self->type)
	{
		case POSTFIX_INDEX:
			puts("[]");
			expression_print_tree(self->expression, depth + 1);
			break;

		case POSTFIX_CALL:
			puts("()");
			parameter_list_print_tree(&self->parameters, depth + 1);
			break;

		case POSTFIX_MEMBER:
			puts(".");
			identifier_print_tree(&self->identifier, depth + 1);
			break;
	}
}
