#include <warbler/ast/expression/expression.hpp>

// standard headers
#include <cassert>

namespace warbler
{
	Expression::Expression(AssignmentExpression&& assignment) :
	_assignment(assignment)
	{}

	Result<Expression> Expression::parse(TokenIterator& iter)
	{
		auto res = AssignmentExpression::parse(iter);

		if (res.has_error())
			return res.error();

		return Expression(res.unwrap());
	}

	void Expression::print_tree(u32 depth) const
	{
		_assignment.print_tree(depth);
	}
}
