#include <warbler/ast/expression/conditional.h>

// standard headers
#include <stdlib.h>

void conditional_expression_init(ConditionalExpression *conditional)
{
	assert(conditional != NULL);

	conditional->lhs = malloc(sizeof(BooleanOrExpression));
	conditional->type = CONDITIONAL_BINARY;
}

void conditional_expression_free(ConditionalExpression *conditional)
{
	assert(conditional != NULL);

	boolean_or_expression_free(conditional->lhs);
	free(conditional->lhs);
}

Error conditional_expression_parse(ConditionalExpression *out, TokenIterator *iter)
{
	assert(out != NULL);
	assert(iter != NULL);

	conditional_expression_init(out);

	Error error;
	if ((error = boolean_or_expression_parse(out->lhs, iter)))
	{
		conditional_expression_free(out);
		return ERROR_ARGUMENT;
	}

	return ERROR_NONE;
}
