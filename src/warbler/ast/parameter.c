#include <warbler/ast/parameter.h>

// standard headers
#include <stdlib.h>

static Error parameter_allocate(Parameter *parameter)
{
	parameter->typename = malloc(sizeof(*parameter->typename));
	parameter->identifier = malloc(sizeof(*parameter->identifier));

	if (!parameter->typename || !parameter->identifier)
	{
		parameter_free(parameter);

		return ERROR_MEMORY;
	}

	return ERROR_NONE;
}

Error parameter_parse(Parameter *out, TokenIterator *iter)
{
	Identifier identifier;
	Error error = identifier_parse(&identifier, iter);

	if (error)
		return error;

	if (iter->token->type != TOKEN_COLON)
		return ERROR_ARGUMENT;

	++iter->token;

	Typename typename;
	error = typename_parse(&typename, iter);
	
	if (error)	
		return error;

	error = parameter_allocate(out);

	if (error)
		return error;

	*out->typename = typename;
	*out->identifier = identifier;

	return ERROR_NONE;
}

void parameter_free(Parameter *parameter)
{
	free(parameter->typename);
	free(parameter->identifier);
}

Error parameter_list_parse(ParameterList *out, TokenIterator *iter)
{
	if (iter->token->type != TOKEN_LPAREN)
		return ERROR_ARGUMENT;

	++iter->token;

	if (iter->token->type != TOKEN_RPAREN)
	{
		while (true)
		{
			Parameter parameter;
			Error error = parameter_parse(&parameter, iter);

			if (error)
			{
				parameter_list_free(out);
				return error;
			}

			++out->count;
			Parameter *tmp = realloc(out->parameters, out->count * sizeof(Parameter));
			if (!tmp)
			{
				parameter_free(&parameter);
				parameter_list_free(out);
				return ERROR_MEMORY;
			}

			out->parameters[out->count - 1] = parameter;
			++out->count;

			if (iter->token->type != TOKEN_COMMA)
				break;
			
			++iter->token;
		}

		if (iter->token->type != TOKEN_RPAREN)
		{
			// TODO: syntax error
			parameter_list_free(out);
			return ERROR_ARGUMENT;
		}

	}

	++iter->token;

	return ERROR_NONE;
}

void parameter_list_free(ParameterList* list)
{
	for (size_t i = 0; i < list->count; ++i)
	{
		parameter_free(list->parameters + i);
	}

	free(list->parameters);
}
