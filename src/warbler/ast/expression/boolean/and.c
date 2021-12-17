#include <warbler/ast/expression/boolean/and.h>

// standard headers
#include <stdlib.h>

void boolean_and_expression_init(BooleanAndExpression *and)
{
	assert(and != NULL);

	and->lhs = NULL;
	and->rhs = NULL;
}

void boolean_and_expression_free(BooleanAndExpression *and)
{
	if (and->lhs)
	{
		bitwise_or_expression_free(and->lhs);
		free(and->lhs);
	}

	if (and->rhs_count)
	{
		for (size_t i = 0; i < and->rhs_count; ++i)
			bitwise_or_expression_free(and->rhs + i);

		free(and->rhs);
	}
}

static inline Error try_boolean_and_expression_parse(BooleanAndExpression *and, TokenIterator *iter)
{
	return ERROR_NONE;
}

Error boolean_and_expression_parse(BooleanAndExpression *and, TokenIterator *iter)
{
	assert(and != NULL);
	assert(iter != NULL);

	boolean_and_expression_init(and);

	Error error = try_boolean_and_expression_parse(and, iter);

	if (error)
		boolean_and_expression_free(and);

	return error;
}
