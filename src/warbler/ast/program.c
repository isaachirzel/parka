#include <warbler/ast/program.h>

// standard headers
#include <stdlib.h>

Error program_parse(Program *out, TokenIterator *iter)
{
	*out = (Program)
	{
		.functions = NULL,
		.function_count = 0
	};

	Function *tmp = realloc(out->functions, (out->function_count + 1) * sizeof(Function));
	if (!tmp)
	{
		program_free(out);
		return ERROR_MEMORY;
	}

	Function *function = out->functions + out->function_count++;
	Error error = function_parse(function, iter);

	if (error)
		program_free(out);

	return error;
}

void program_free(Program *program)
{
	for (size_t i = 0; i < program->function_count; ++i)
	{
		function_free(program->functions + i);
	}
}
