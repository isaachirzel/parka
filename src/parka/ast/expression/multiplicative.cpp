#include "parka/ast/expression/multiplicative.hpp"
#include "parka/ast/expression/prefix.hpp"
#include "parka/entity/node_bank.hpp"
#include "parka/util/print.hpp"

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

Optional<ExpressionId> MultiplicativeExpression::parse(Token& token)
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

		auto expression = MultiplicativeExpression(lhs.unwrap(), rhs.unwrap(), type.unwrap());
		auto id = NodeBank::add(std::move(expression));

		lhs = std::move(id);
		type = getMultiplicativeType(token);
	}

	return lhs;
}

bool MultiplicativeExpression::validate(SymbolTable& symbols)
{
	auto success = true;

	if (!NodeBank::get(_lhs).validate(symbols))
		success = false;

	if (!NodeBank::get(_rhs).validate(symbols))
		success = false;

	return success;
}

Optional<Type> MultiplicativeExpression::getType(const SymbolTable& symbolTable, Ref<Type> expected) const
{
	exitNotImplemented();
}
