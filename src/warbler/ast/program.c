#include <warbler/ast/program.h>

// standard headers
#include <stdlib.h>

void program_init(Program *self)
{
	assert(self != NULL);

	self->functions = NULL;
	self->function_count = 0;
}

void program_free(Program *self)
{
	if (!self)
		return;

	for (size_t i = 0; i < self->function_count; ++i)
	{
		function_free(self->functions + i);
	}

	free(self->functions);
}

static inline Error increment_functions(Program *self)
{
	size_t new_size = (self->function_count + 1) * sizeof(Function);
	Function *tmp = realloc(self->functions, new_size);

	if (!tmp)
		return ERROR_MEMORY;

	self->functions = tmp;

	Function *back = self->functions + self->function_count++;

	function_init(back);

	return ERROR_NONE;
}

Error program_parse(Program *self, TokenIterator *iter)
{
	assert(self != NULL);
	assert(iter != NULL);

	program_init(self);

	Error error;

	while (iter->token->type != TOKEN_END_OF_FILE)
	{		
		if ((error = increment_functions(self)))
			return error;

		Function *back = self->functions + (self->function_count - 1);

		if ((error = function_parse(back, iter)))
			return error;
	}

	return ERROR_NONE;
}
