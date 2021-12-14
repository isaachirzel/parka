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
		postfix_expression_free(prefix->postfix);
	}
	else
	{
		prefix_expression_free(prefix->prefix);
	}
}

Error prefix_expression_parse(PrefixExpression *prefix, TokenIterator *iter)
{
	Error error;

	switch (iter->token->type)
	{
		default:
			prefix->type = PREFIX_NONE;
			if ((error = postfix_expression_parse(prefix->postfix, iter)))
			{
				prefix_expression_free(prefix);
				return error;
			}

			break;
	}

	return ERROR_NONE;
}
