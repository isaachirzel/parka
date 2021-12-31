#include <warbler/ast/expression/prefix.h>

// local headers
#include <warbler/print.h>

// standard headers
#include <stdlib.h>
#include <assert.h>

void prefix_list_init(PrefixList *self)
{
	assert(self);

	*self = (PrefixList)
	{
		.data = NULL,
		.count = 0
	};
}

void prefix_list_free(PrefixList *self)
{
	if (!self)
		return;

	free(self->data);
}

Error prefix_parse(Prefix *self, TokenIterator *iter)
{
	assert(self);
	assert(iter);

	switch (iter->token->type)
	{
		case TOKEN_INCREMENT:
			self->type = PREFIX_INCREMENT;
			break;

		case TOKEN_DECREMENT:
			self->type = PREFIX_DECREMENT;
			break;

		case TOKEN_AMPERSAND:
			self->type = PREFIX_REFERENCE;
			break;

		case TOKEN_ASTERISK:
			self->type = PREFIX_DEREFERENCE;
			break;

		default:
			return ERROR_ARGUMENT;
	}

	++iter->token;

	return ERROR_NONE;
}

static inline Prefix *prefix_list_push(PrefixList *self)
{
	size_t new_size = (self->count + 1) * sizeof(Prefix);
	Prefix *tmp = realloc(self->data, new_size);

	if (!tmp)
		return NULL;

	Prefix *back = tmp + self->count;

	self->data = tmp;
	++self->count;

	return back;
}

Error prefix_list_parse(PrefixList *self, TokenIterator *iter)
{
	assert(self);
	assert(iter);

	prefix_list_init(self);

	while (true)
	{
		Prefix prefix;

		if (prefix_parse(&prefix, iter) != ERROR_NONE)
			break;

		Prefix *back = prefix_list_push(self);

		if (!back)
			return ERROR_MEMORY;

		*back = prefix;
	}

	return ERROR_NONE;
}

void prefix_print_tree(Prefix *self, unsigned depth)
{
	print_branch(depth);

	switch (self->type)
	{
		case PREFIX_INCREMENT:
			puts("++");
			break;

		case PREFIX_DECREMENT:
			puts("--");
			break;

		case PREFIX_REFERENCE:
			puts("&");
			break;

		case PREFIX_DEREFERENCE:
			puts("*");
			break;
	}
}

void prefix_list_print_tree(PrefixList *self, unsigned depth)
{
	assert(self);
	debugf("prefix count: %zu\n", self->count);

	return;

	for (size_t i = 0; i < self->count; ++i)
		prefix_print_tree(self->data + i, depth + 1);
}
