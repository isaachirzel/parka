#include <warbler/ast/expression/prefix.h>

// standard headers
#include <stdlib.h>

void prefix_expression_init(PrefixExpression *self)
{
	self->type = PREFIX_NONE;
	self->postfix = NULL;
}

void prefix_expression_free(PrefixExpression *self)
{
	if (self->type == PREFIX_NONE)
	{
		if (self->postfix)
			postfix_expression_free(self->postfix);

		free(self->postfix);
	}
	else
	{
		if (self->prefix)
			prefix_expression_free(self->prefix);

		free(self->prefix);
	}
}

static inline Error try_prefix_expression_parse(PrefixExpression *self, TokenIterator *iter)
{
	Error error;

	switch (iter->token->type)
	{
		default:
			self->type = PREFIX_NONE;
			self->postfix = malloc(sizeof(PostfixExpression));

			if (!self->postfix)
				return ERROR_MEMORY;

			if ((error = postfix_expression_parse(self->postfix, iter)))
				return error;
			break;
	}

	return ERROR_NONE;
}

Error prefix_expression_parse(PrefixExpression *self, TokenIterator *iter)
{
	assert(self != NULL);
	assert(iter != NULL);

	prefix_expression_init(self);

	Error error = try_prefix_expression_parse(self, iter);

	if (error)
		prefix_expression_free(self);

	return error;
}
