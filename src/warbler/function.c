#include <warbler/ast/function.h>

// local headers
#include <warbler/print.h>

// standard headers
#include <stdlib.h>

void function_init(Function *function)
{
	assert(function != NULL);

	identifier_init(&function->name);
	parameter_list_init(&function->parameters);
	typename_init(&function->return_type);

	function->is_inline = false;
	function->inline_body = NULL;
}

void function_free(Function *function)
{
	assert(function != NULL);

	identifier_free(&function->name);
	typename_free(&function->return_type);
	parameter_list_free(&function->parameters);

	if (function->is_inline)
	{
		expression_free(function->inline_body);
		free(function->inline_body);
	}
	else
	{
		compound_statement_free(function->compound_body);
		free(function->compound_body);
	}
}

static inline Error function_parse_body(Function *function, TokenIterator *iter)
{
	Error error;

	switch (iter->token->type)
	{
		case TOKEN_DOUBLE_ARROW:
			function->is_inline = true;
			
			if ((error = expression_parse(function->inline_body, iter)))
				return error;

			break;

		case TOKEN_LBRACE:
			function->is_inline = false;

			if ((error = compound_statement_parse(function->compound_body, iter)))
				return error;
			break;

		default:
			errortf(iter->token, "expected function body but got: %t", iter->token);
			return ERROR_ARGUMENT;
	}

	return ERROR_NONE;
}

static inline Error try_function_parse(Function *function, TokenIterator *iter)
{
	Error error;

	if (iter->token->type != TOKEN_FUNC)
		return ERROR_ARGUMENT;

	++iter->token;

	if ((error = identifier_parse(&function->name, iter)))
		return error;

	if ((error = parameter_list_parse(&function->parameters, iter)))
		return error;
		
	if (iter->token->type == TOKEN_SINGLE_ARROW)
	{
		++iter->token;

		if ((error = typename_parse(&function->return_type, iter)))
			return error;
	}

	if ((error = function_parse_body(function, iter)))
		return error;

	return ERROR_NONE;
}

Error function_parse(Function *function, TokenIterator *iter)
{
	assert(function != NULL);
	assert(iter != NULL);

	function_init(function);

	Error error = try_function_parse(function, iter);

	if (error)
		function_free(function);
		
	return error;
}
