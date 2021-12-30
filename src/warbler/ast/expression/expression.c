#include <warbler/ast/expression/expression.h>

void expression_init(Expression *self)
{
	assignment_expression_init(&self->assignment);
}

void expression_free(Expression *self)
{
	assignment_expression_free(&self->assignment);
}

Error expression_parse(Expression *self, TokenIterator *iter)
{
	return assignment_expression_parse(&self->assignment, iter);
}

void expression_print_tree(Expression *self, unsigned depth)
{
	assignment_expression_print_tree(&self->assignment, depth);
}
