#include "parka/ast/expression/bitwise_xor.hpp"
#include "parka/ast/expression/bitwise_and.hpp"
#include "parka/symbol/node_bank.hpp"
#include "parka/util/print.hpp"

Optional<ExpressionId> BitwiseXorExpression::parse(Token& token)
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

		auto expression = BitwiseXorExpression(lhs.unwrap(), rhs.unwrap());
		auto id = NodeBank::add(std::move(expression));

		lhs = std::move(id);
	}

	return lhs;
}

bool BitwiseXorExpression::validate(const EntityId&)
{
	exitNotImplemented(here());
}

Optional<Type> BitwiseXorExpression::getType() const
{
	exitNotImplemented(here());
}
