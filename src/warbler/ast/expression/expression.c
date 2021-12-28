#include <warbler/ast/expression/expression.h>

void expression_init(Expression *expression)
{
	assignment_expression_init(&expression->assignment);
}

void expression_free(Expression *expression)
{
	assignment_expression_free(&expression->assignment);
}

static inline Error try_expression_parse(Expression *expression, TokenIterator *iter)
{
	Error error;
	
	if ((error = assignment_expression_parse(&expression->assignment, iter)))
		return error;

	return ERROR_NONE;
}

Error expression_parse(Expression *expression, TokenIterator *iter)
{
	assert(expression != NULL);
	assert(iter != NULL);

	expression_init(expression);

	Error error = assignment_expression_parse(&expression->assignment, iter);

	if (error)
		expression_free(expression);

	return error;
}
