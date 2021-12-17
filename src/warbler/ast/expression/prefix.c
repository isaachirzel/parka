#include <warbler/ast/expression/prefix.h>

// standard headers
#include <stdlib.h>

void prefix_expression_init(PrefixExpression *prefix)
{
	prefix->type = PREFIX_NONE;
	prefix->postfix = NULL;
}

void prefix_expression_free(PrefixExpression *prefix)
{

	if (prefix->type == PREFIX_NONE)
	{
		if (prefix->postfix)
			postfix_expression_free(prefix->postfix);
	}
	else
	{
		if (prefix->prefix)
			prefix_expression_free(prefix->prefix);
	}
}

static inline Error try_prefix_expression_parse(PrefixExpression *prefix, TokenIterator *iter)
{
	Error error;

	switch (iter->token->type)
	{
		default:
			prefix->type = PREFIX_NONE;
			if ((error = postfix_expression_parse(prefix->postfix, iter)))
				return error;
			break;
	}

	return ERROR_NONE;
}

Error prefix_expression_parse(PrefixExpression *prefix, TokenIterator *iter)
{
	assert(prefix != NULL);
	assert(iter != NULL);

	prefix_expression_init(prefix);

	Error error = try_prefix_expression_parse(prefix, iter);

	if (error)
		prefix_expression_free(prefix);

	return error;
}
