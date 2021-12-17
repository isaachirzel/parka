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

static inline Error try_conditional_expression_parse(ConditionalExpression *out, TokenIterator *iter)
{
	
	return ERROR_NONE;
}

Error conditional_expression_parse(ConditionalExpression *conditional, TokenIterator *iter)
{
	assert(conditional != NULL);
	assert(iter != NULL);

	conditional_expression_init(conditional);

	Error error = try_conditional_expression_parse(conditional, iter);

	if (error)
		conditional_expression_free(conditional);

	return error;
}
