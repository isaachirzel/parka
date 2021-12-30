#include <warbler/ast/parameter.h>

// local headers
#include <warbler/print.h>

// standard headers
#include <stdlib.h>

void parameter_init(Parameter *parameter)
{
	identifier_init(&parameter->name);
	typename_init(&parameter->type);
}

void parameter_free(Parameter *parameter)
{
	identifier_free(&parameter->name);
	typename_free(&parameter->type);
}

static inline Error try_parameter_parse(Parameter *parameter, TokenIterator *iter)
{
	Error error;

	if ((error = identifier_parse(&parameter->name, iter)))
		return error;

	if (iter->token->type != TOKEN_COLON)
		return ERROR_ARGUMENT;

	++iter->token;

	if ((error = typename_parse(&parameter->type, iter)))
		return error;

	return ERROR_NONE;
}

Error parameter_parse(Parameter *parameter, TokenIterator *iter)
{
	assert(parameter != NULL);
	assert(iter != NULL);

	parameter_init(parameter);

	Error error = try_parameter_parse(parameter, iter);

	if (error)
		parameter_free(parameter);

	return error;
}

void parameter_list_init(ParameterList *list)
{
	list->parameters = NULL;
	list->parameter_count = 0;
}

void parameter_list_free(ParameterList *list)
{
	for (size_t i = 0; i < list->parameter_count; ++i)
	{
		parameter_free(list->parameters + i);
	}

	free(list->parameters);
}

static inline Error increment_parameters(ParameterList *list)
{
	size_t new_size = (list->parameter_count + 1) * sizeof(Parameter);
	Parameter *tmp = realloc(list->parameters, new_size);

	if (!tmp)
		return ERROR_MEMORY;

	list->parameters = tmp;

	Parameter *back = list->parameters + list->parameter_count++;

	parameter_init(back);

	return ERROR_NONE;
}

Error try_parameter_list_parse(ParameterList *list, TokenIterator *iter)
{
	Error error;

	if (iter->token->type != TOKEN_LPAREN)
		return ERROR_ARGUMENT;

	++iter->token;

	if (iter->token->type != TOKEN_RPAREN)
	{
		while (true)
		{
			if ((error = increment_parameters(list)))
				return error;

			Parameter *back = list->parameters + (list->parameter_count - 1);

			if ((error = parameter_parse(back, iter)))
				return error;

			if (iter->token->type != TOKEN_COMMA)
				break;
			
			++iter->token;
		}

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

Error parameter_list_parse(ParameterList *list, TokenIterator *iter)
{
	assert(list != NULL);
	assert(iter != NULL);

	parameter_list_init(list);

	Error error = try_parameter_list_parse(list, iter);

	if (error)
		parameter_list_free(list);

	return error;
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

	for (size_t i = 0; i < self->parameter_count; ++i)
	{
		parameter_print_tree(self->parameters + i, depth + 1);
	}
}
