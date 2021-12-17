#include <warbler/ast/expression/boolean/or.h>

// standard headers
#include <stdlib.h>

void boolean_or_expression_init(BooleanOrExpression *or)
{
	assert(or != NULL);

	or->lhs = NULL;
	or->rhs = NULL;
}

void boolean_or_expression_free(BooleanOrExpression *or)
{
	assert(or != NULL);

	if (or->lhs)
	{
		boolean_and_expression_free(or->lhs);
		free(or->lhs);
	}
	
	if (or->rhs_count > 0)
	{
		for (size_t i = 0; i < or->rhs_count; ++i)
			boolean_and_expression_free(or->rhs + i);

		free(or->rhs);
	}
}

static inline Error try_boolean_or_expression_parse(BooleanOrExpression *or, TokenIterator *iter)
{
	return ERROR_NONE;
}

Error boolean_or_expression_parse(BooleanOrExpression *or, TokenIterator *iter)
{
	assert(or != NULL);
	assert(iter != NULL);

	boolean_or_expression_init(or);

	Error error = try_boolean_or_expression_parse(or, iter);

	if (error)
		boolean_or_expression_free(or);

	return error;
}
