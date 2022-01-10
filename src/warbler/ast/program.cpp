#include <warbler/ast/program.hpp>

// standard headers
#include <cstdlib>
#include <cassert>

namespace warbler
{
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

static inline Function *program_push(Program *self)
{
	size_t new_size = (self->function_count + 1) * sizeof(Function);
	Function *tmp = (Function*)realloc(self->functions, new_size);

	if (!tmp)
		return NULL;

	Function *back = tmp + self->function_count++;

	self->functions = tmp;
	++self->function_count;

	return back;
}

Error program_parse(Program *self, TokenIterator& iter)
{
	assert(self != NULL);
	

	program_init(self);

	while (iter->type != TOKEN_END_OF_FILE)
	{		
		Function *back = program_push(self);

		if (!back)
			return ERROR_MEMORY;

		try(function_parse(back, iter));
	}

	return ERROR_NONE;
}
}