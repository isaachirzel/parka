#include "parka/ast/expression/boolean_and.hpp"
#include "parka/ast/expression/bitwise_or.hpp"
#include "parka/ast/expression/expression.hpp"
#include "parka/entity/node_bank.hpp"


Optional<ExpressionId> BooleanAndExpression::parse(Token& token)
{
	auto lhs = BitwiseOrExpression::parse(token);

	if (!lhs)
		return {};

	while (token.type() == TokenType::BooleanAnd)
	{
		token.increment();

		auto rhs = BitwiseOrExpression::parse(token);

		if (!rhs)
			return {};

		auto expression = BooleanAndExpression(lhs.unwrap(), rhs.unwrap());
		auto id = NodeBank::add(std::move(expression));

		lhs = std::move(id);
	}

	return lhs;
}
