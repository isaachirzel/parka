#include <warbler/ast/expression/expression.h>

Error expression_parse(Expression *out, TokenIterator *iter)
{
	Assignment assignment;
	Error error = assignment_parse(&assignment, iter);

	if (error)
		return error;
	
	*out->assignment = assignment;

	return ERROR_NONE;
}

void expression_free(Expression *expression)
{
	assignment_free(expression->assignment);
}
