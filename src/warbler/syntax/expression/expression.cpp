#include <warbler/syntax/expression/expression.hpp>

#include <warbler/syntax/expression/conditional_expression.hpp>

namespace warbler::syntax
{
	Result<Ptr<Expression>> Expression::parse(lexicon::TokenIterator& iter)
	{
		auto res = ConditionalExpression::parse(iter);

		if (!res)
			return {};

		return Ptr<Expression> { new ConditionalExpression(res.unwrap()) };
	}
}
