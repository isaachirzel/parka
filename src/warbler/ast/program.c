#include <warbler/ast/program.h>

// standard headers
#include <stdlib.h>

void program_init(Program *out)
{
	assert(out != NULL);

	out->functions = NULL;
	out->function_count = 0;
}

void program_free(Program *out)
{
	assert(out != NULL);

	for (size_t i = 0; i < out->function_count; ++i)
	{
		function_free(out->functions + i);
	}

	free(out->functions);
}

static inline Error increment_functions(Program *out)
{
	size_t new_size = (out->function_count + 1) * sizeof(Function);
	Function *tmp = realloc(out->functions, new_size);

	if (!tmp)
		return ERROR_MEMORY;

	out->functions = tmp;

	Function *back = out->functions + out->function_count++;

	function_init(back);

	return ERROR_NONE;
}

static inline Error try_program_parse(Program *out, TokenIterator *iter)
{
	Error error;

	while (iter->token->type != TOKEN_END_OF_FILE)
	{		
		if ((error = increment_functions(out)))
			return error;

		Function *back = out->functions + (out->function_count - 1);

		if ((error = function_parse(back, iter)))
			return error;
	}

	return ERROR_NONE;
}

Error program_parse(Program *out, TokenIterator *iter)
{
	assert(out != NULL);
	assert(iter != NULL);

	program_init(out);

	Error error = try_program_parse(out, iter);

	if (error)
		program_free(out);

	return error;
}
