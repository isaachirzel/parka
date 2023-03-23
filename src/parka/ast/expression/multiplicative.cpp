#include "parka/ast/expression/multiplicative.hpp"
#include "parka/ast/expression/prefix.hpp"

Optional<MultiplicativeType> getMultiplicativeType(Token& token)
{
	switch (token.type())
	{
		case TokenType::Modulus:
			return MULTIPLICATIVE_MODULUS;

		case TokenType::Asterisk:
			return MULTIPLICATIVE_MULTIPLY;

		case TokenType::Slash:
			return MULTIPLICATIVE_DIVIDE;

		default:
			return {};
	}
}

Optional<Box<Expression>> MultiplicativeExpression::parse(Token& token)
{
	auto lhs = Prefix::parse(token);

	if (!lhs)
		return {};
	
	auto type = getMultiplicativeType(token);

	while (type)
	{
		token.increment();
		
		auto rhs = Prefix::parse(token);

		if (!rhs)
			return {};

		auto *expression = new MultiplicativeExpression(lhs.unwrap(), rhs.unwrap(), type.unwrap());
		auto box = Box<Expression>(expression);

		lhs = Optional(std::move(box));
		type = getMultiplicativeType(token);
	}

	return lhs;
}

bool MultiplicativeExpression::validate(SymbolTable& symbols)
{
	bool success = true;

	if (!_lhs->validate(symbols))
		success = false;

	if (!_rhs->validate(symbols))
		success = false;

	return success;
}
