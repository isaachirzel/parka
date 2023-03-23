#include "parka/ast/expression/equality.hpp"
#include "parka/ast/expression/relational.hpp"


Optional<EqualityType> getEqualityType(Token& token)
{
	switch (token.type())
	{
		case TokenType::Equals:
			return EQUALITY_EQUALS;

		case TokenType::NotEquals:
			return EQUALITY_NOT_EQUALS;

		default:
			return {};
	}
}

Optional<Box<Expression>> EqualityExpression::parse(Token& token)
{
	auto lhs = RelationalExpression::parse(token);

	if (!lhs)
		return {};

	auto type = getEqualityType(token);

	while (type)
	{
		token.increment();

		auto rhs = RelationalExpression::parse(token);

		if (!rhs)
			return {};

		auto *expression = new EqualityExpression(lhs.unwrap(), rhs.unwrap(), type.unwrap());
		auto box = Box<Expression>(expression);

		lhs = Optional(std::move(box));
		type = getEqualityType(token);
	}

	return lhs;
}
