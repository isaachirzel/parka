#include <warbler/ast/typename.hpp>

// standard headers
#include <cstdlib>
#include <cassert>

namespace warbler
{
	void typename_init(Typename *self)
	{
		assert(self);

		self->text = NULL;
	}

	void typename_free(Typename *self)
	{
		if (!self)
			return;

		free(self->text);
	}

	Error typename_parse(Typename *self, TokenIterator& iter)
	{
		assert(self);
		

		typename_init(self);
		
		if (iter->type != TOKEN_IDENTIFIER)
			return ERROR_ARGUMENT;

		self->text = string_duplicate(&iter->text);

		if (!self->text)
			return ERROR_MEMORY;

		return ERROR_NONE;
	}
}