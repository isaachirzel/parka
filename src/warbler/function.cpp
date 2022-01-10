#include <warbler/ast/function.hpp>

// local headers
#include <warbler/print.hpp>

// standard headers
#include <cstdlib>
#include <cassert>

namespace warbler
{
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

	static inline Error function_parse_body(Function *function, TokenIterator& iter)
	{
		Error error;

		switch (iter->type)
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
				errortf(*iter, "expected function body but got: %t", iter);
				return ERROR_ARGUMENT;
		}

		return ERROR_NONE;
	}

	static inline Error try_function_parse(Function *function, TokenIterator& iter)
	{
		Error error;

		if (iter->type != TOKEN_FUNC)
			return ERROR_ARGUMENT;

		++iter;

		if ((error = identifier_parse(&function->name, iter)))
			return error;

		if ((error = parameter_list_parse(&function->parameters, iter)))
			return error;
			
		if (iter->type == TOKEN_SINGLE_ARROW)
		{
			++iter;

			if ((error = typename_parse(&function->return_type, iter)))
				return error;
		}

		if ((error = function_parse_body(function, iter)))
			return error;

		return ERROR_NONE;
	}

	Error function_parse(Function *function, TokenIterator& iter)
	{
		assert(function != NULL);
		

		function_init(function);

		Error error = try_function_parse(function, iter);

		if (error)
			function_free(function);
			
		return error;
	}
}