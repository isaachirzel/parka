#include <warbler/ast/parameter.h>

// local headers
#include <warbler/print.h>

// standard headers
#include <stdlib.h>

void parameter_init(Parameter *self)
{
	assert(self);

	identifier_init(&self->name);
	typename_init(&self->type);
}

void parameter_free(Parameter *self)
{
	if (!self)
		return;

	identifier_free(&self->name);
	typename_free(&self->type);
}

Error parameter_parse(Parameter *self, TokenIterator *iter)
{
	assert(self);
	assert(iter);

	parameter_init(self);

	Error error;
	
	if ((error = identifier_parse(&self->name, iter)))
		return error;

	debug("parsed parameter");

	if (iter->token->type != TOKEN_COLON)
		return ERROR_ARGUMENT;

	++iter->token;

	if ((error = typename_parse(&self->type, iter)))
		return error;

	return ERROR_NONE;
}

void parameter_list_init(ParameterList *self)
{
	*self = (ParameterList)
	{
		.data = NULL,
		.count = 0
	};
}

void parameter_list_free(ParameterList *self)
{
	for (size_t i = 0; i < self->count; ++i)
		parameter_free(self->data + i);

	free(self->data);
}

static inline Error push_parameter(ParameterList *self, Parameter *parameter)
{
	size_t new_size = (self->count + 1) * sizeof(Parameter);
	Parameter *tmp = realloc(self->data, new_size);

	if (!tmp)
		return ERROR_MEMORY;

	tmp[self->count] = *parameter;

	self->data = tmp;
	++self->count;

	return ERROR_NONE;
}

Error parameter_list_parse(ParameterList *self, TokenIterator *iter)
{
	assert(self);
	assert(iter);

	parameter_list_init(self);

	Error error;

	if (iter->token->type != TOKEN_LPAREN)
		return ERROR_ARGUMENT;

	debugf("token type: %d\n", iter->token->type);

	if (iter->token[1].type != TOKEN_RPAREN)
	{
		do
		{
			++iter->token;

			Parameter parameter;
			if ((error = parameter_parse(&parameter, iter)))
				return error;

			if ((error = push_parameter(self, &parameter)))
				return error;			
		}
		while (iter->token->type == TOKEN_COMMA);

		if (iter->token->type != TOKEN_RPAREN)
		{
			print_error("expected ',' or ')' after parameter but got: ");
			token_print(iter->token);

			return ERROR_ARGUMENT;
		}
	}

	++iter->token;

	return ERROR_NONE;
}

void parameter_print_tree(Parameter *self, unsigned depth)
{
	assert(self != NULL);

	print_branch(depth);
	printf("%s: %s\n", self->name.text, self->type.text);
}

void parameter_list_print_tree(ParameterList *self, unsigned depth)
{
	assert(self != NULL);

	for (size_t i = 0; i < self->count; ++i)
	{
		parameter_print_tree(self->data + i, depth + 1);
	}
}
