#include "parka/ast/expression/boolean_and.hpp"
#include "parka/ast/expression/bitwise_or.hpp"
#include "parka/ast/expression/expression.hpp"


Optional<Box<Expression>> BooleanAndExpression::parse(Token& token)
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

		auto *expression = new BooleanAndExpression(lhs.unwrap(), rhs.unwrap());
		auto box = Box<Expression>(expression);

		lhs = Optional(std::move(box));
		
	}

	return lhs;
}
