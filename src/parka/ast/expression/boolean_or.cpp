#include "parka/ast/expression/boolean_or.hpp"
#include "parka/ast/expression/boolean_and.hpp"


Optional<Box<Expression>> BooleanOrExpression::parse(Token& token)
{
	auto lhs = BooleanAndExpression::parse(token);

	if (!lhs)
		return {};

	while (token.type() == TokenType::BooleanOr)
	{
		token.increment();

		auto rhs = BooleanAndExpression::parse(token);

		if (!rhs)
			return {};

		auto *expression = new BooleanOrExpression(lhs.unwrap(), rhs.unwrap());
		auto box = Box<Expression>(expression);

		lhs = Optional(std::move(box));
	}

	return lhs;
}
