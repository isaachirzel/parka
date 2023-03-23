#include "parka/ast/expression/bitwise_or.hpp"
#include "parka/ast/expression/bitwise_xor.hpp"


Optional<Box<Expression>> BitwiseOrExpression::parse(Token& token)
{
	auto lhs = BitwiseXorExpression::parse(token);

	if (!lhs)
		return {};

	while (token.type() == TokenType::Pipe)
	{
		token.increment();

		auto rhs = BitwiseXorExpression::parse(token);

		if (!rhs)
			return {};

		auto *expression = new BitwiseOrExpression(lhs.unwrap(), rhs.unwrap());
		auto box = Box<Expression>(expression);

		lhs = Optional(std::move(box));
		
	}

	return lhs;
}
