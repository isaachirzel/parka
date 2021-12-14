#include <warbler/ast/function.h>

void function_init(Function *function)
{
	typename_init(&function->return_type);
	identifier_init(&function->name);
	function->parameters = NULL;
	function->is_inline = false;
	function->body.compound = NULL;
}

void function_free(Function *function)
{
	typename_free(&function->return_type);
	identifier_free(&function->name);
	parameter_list_free(function->parameters);

	if (function->is_inline)
	{
		expression_free(function->body.expression);
	}
	else
	{
		compound_statement_free(function->body.compound);
	}
}

Error function_parse(Function *function, TokenIterator *iter)
{
	if (iter->token->type != TOKEN_FUNC)
		return ERROR_ARGUMENT;

	++iter->token;

	Error error;
	if ((error = identifier_parse(&function->name, iter)))
		return ERROR_ARGUMENT;

	if ((error = parameter_list_parse(function->parameters, iter)))
	{
		function_free(function);
		return ERROR_ARGUMENT;
	}	

	if (iter->token->type == TOKEN_SINGLE_ARROW)
	{
		++iter->token;

		if ((error = typename_parse(&function->return_type, iter)))
		{
			function_free(function);
			return ERROR_ARGUMENT;
		}
	}

	switch (iter->token->type)
	{
		case TOKEN_DOUBLE_ARROW:
			function->is_inline = true;

			if ((error = expression_parse(function->body.expression, iter)))
			{
				function_free(function);
				return ERROR_ARGUMENT;
			}
			break;

		case TOKEN_LBRACE:
			if ((error = compound_statement_parse(function->body.compound, iter)))
			{
				function_free(function);
				return ERROR_ARGUMENT;
			}
			break;

		default:
			print_error("invalid token given for function body");
			function_free(function);
			return ERROR_ARGUMENT;
	}

	return ERROR_NONE;
}
