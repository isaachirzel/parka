#include <warbler/ast/expression/expression.hpp>

#include <warbler/ast/expression/conditional_expression.hpp>

namespace warbler::ast
{
	Result<Ptr<Expression>> Expression::parse(TokenIterator& iter)
	{
		auto res = ConditionalExpression::parse(iter);

		if (!res)
			return {};

		return Ptr<Expression> { new ConditionalExpression(res.unwrap()) };
	}
}
