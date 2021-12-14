#include <warbler/ast/expression/postfix.h>

// standard headers
#include <assert.h>

void postfix_expression_init(PostfixExpression *postfix)
{
	postfix->type = POSTFIX_NONE;
	postfix->primary = NULL;
}

void postfix_expression_free(PostfixExpression *postfix)
{
	if (postfix->type == POSTFIX_NONE)
	{
		primary_expression_free(postfix->primary);
	}
	else
	{
		postfix_expression_free(postfix->postifx);
	}
}

Error postfix_expression_parse(PostfixExpression *postfix, TokenIterator *iter)
{
	assert(postfix != NULL);
	assert(iter != NULL);

	return not_implemented_error();
}
