#include "parka/ast/expression/bitwise_and.hpp"
#include "parka/ast/expression/equality.hpp"
#include "parka/ast/expression/expression.hpp"
#include "parka/token.hpp"
#include "parka/util/optional.hpp"

Optional<Box<Expression>> BitwiseAndExpression::parse(Token& token)
{
	auto lhs = EqualityExpression::parse(token);

	if (!lhs)
		return {};

	while (token.type() == TokenType::Ampersand)
	{
		token.increment();

		auto rhs = EqualityExpression::parse(token);

		if (!rhs)
			return {};

		auto *expression = new BitwiseAndExpression(lhs.unwrap(), rhs.unwrap());
		auto box = Box<Expression>(expression);

		lhs = Optional(std::move(box));
		
	}

	return lhs;
}
