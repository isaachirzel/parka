#include "parka/ast/expression/bitwise_xor.hpp"
#include "parka/ast/expression/bitwise_and.hpp"


Optional<Box<Expression>> BitwiseXorExpression::parse(Token& token)
{
	auto lhs = BitwiseAndExpression::parse(token);

	if (!lhs)
		return {};

	while (token.type() == TokenType::Carrot)
	{
		token.increment();

		auto rhs = BitwiseAndExpression::parse(token);

		if (!rhs)
			return {};

		auto *expression = new BitwiseXorExpression(lhs.unwrap(), rhs.unwrap());
		auto box = Box<Expression>(expression);

		lhs = Optional(std::move(box));
		
	}

	return lhs;
}
