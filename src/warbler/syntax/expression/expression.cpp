#include <warbler/syntax/expression/expression.hpp>

#include <warbler/syntax/expression/conditional_expression.hpp>

namespace warbler::syntax
{
	Result<Ptr<Expression>> Expression::parse(lexicon::Token& token)
	{
		auto res = ConditionalExpression::parse(token);

		if (!res)
			return {};

		return Ptr<Expression> { new ConditionalExpression(res.unwrap()) };
	}
}
