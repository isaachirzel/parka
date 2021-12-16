#include <warbler/ast/program.h>

// standard headers
#include <stdlib.h>

void program_init(Program *program)
{
	assert(program != NULL);

	program->functions = NULL;
	program->function_count = 0;
}

void program_free(Program *program)
{
	assert(program != NULL);

	for (size_t i = 0; i < program->function_count; ++i)
	{
		function_free(program->functions + i);
	}

	free(program->functions);
}

static inline Error increment_functions(Program *program)
{
	size_t new_size = (program->function_count + 1) * sizeof(Function);
	Function *tmp = realloc(program->functions, new_size);

	if (!tmp)
		return ERROR_MEMORY;

	program->functions = tmp;

	Function *back = program->functions + program->function_count++;

	function_init(back);

	return ERROR_NONE;
}

static inline Error try_program_parse(Program *program, TokenIterator *iter)
{
	while (iter->token->type != TOKEN_END_OF_FILE)
	{		
		try(increment_functions(program));

		Function *back = program->functions + (program->function_count - 1);

		try(function_parse(back, iter));
	}

	return ERROR_NONE;
}

Error program_parse(Program *program, TokenIterator *iter)
{
	assert(program != NULL);
	assert(iter != NULL);

	program_init(program);

	Error error = try_program_parse(program, iter);

	if (error)
		program_free(program);

	return error;
}
