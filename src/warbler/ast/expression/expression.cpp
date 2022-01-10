#include <warbler/ast/expression/expression.hpp>

#include <cassert>

namespace warbler
{
	void expression_init(Expression *self)
	{
		assert(self);

		assignment_expression_init(&self->assignment);
	}

	void expression_free(Expression *self)
	{
		if (!self)
			return;
			
		assignment_expression_free(&self->assignment);
	}

	Error expression_parse(Expression *self, TokenIterator& iter)
	{
		assert(self);
		

		expression_init(self);

		return assignment_expression_parse(&self->assignment, iter);
	}

	void expression_print_tree(Expression *self, unsigned depth)
	{
		assignment_expression_print_tree(&self->assignment, depth);
	}
}
