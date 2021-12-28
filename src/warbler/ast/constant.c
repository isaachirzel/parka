#include <warbler/ast/constant.h>

// standard headers
#include <assert.h>
#include <stdlib.h>

void constant_init(Constant *constant)
{
	assert(constant != NULL);

	constant->type = CONSTANT_INTEGER;
	constant->integer = 0;
}

void constant_free(Constant *constant)
{
	assert(constant != NULL);

	if (constant->type == CONSTANT_STRING)
		free(constant->string);
}


static inline Error try_constant_parse(Constant *self, TokenIterator *iter)
{
	switch (self->type)
	{
		case TOKEN_INTEGER_LITERAL:
			break;

		case TOKEN_FLOAT_LITERAL:
			break;

		case TOKEN_HEXADECIMAL_LITERAL:
			break;

		case TOKEN_BINARY_LITERAL:
			break;

		case TOKEN_OCTAL_LITERAL:
			break;

		case TOKEN_CHAR_LITERAL:
			
			break;

		case TOKEN_STRING_LITERAL:
			self->string = string_duplicate(iter->token);

			if (!self->string)
				return ERROR_MEMORY;
			break;

		case TOKEN_TRUE:
			break;

		case TOKEN_FALSE:
			break;
	}
}

Error constant_parse(Constant *self, TokenIterator *iter)
{
	assert(self != NULL);
	assert(iter != NULL);

	constant_init(self);

	Error error = try_constant_parse(self, iter);

	if (error)
		constant_free(self);

	return error;
}
