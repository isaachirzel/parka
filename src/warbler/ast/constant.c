#include <warbler/ast/constant.h>

// standard headers
#include <assert.h>
#include <stdlib.h>

void constant_init(Constant *constant)
{
	assert(constant != NULL);

	constant->type = CONSTANT_INTEGER;
	constant->text = NULL;
}

void constant_free(Constant *constant)
{
	assert(constant != NULL);

	free(constant->text);
}

Error constant_parse(Constant *out, TokenIterator *iter)
{
	assert(out != NULL);
	assert(iter != NULL);

	return not_implemented_error();
}
