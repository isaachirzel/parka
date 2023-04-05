#include "parka/ast/bitwise_xor_expression.hpp"
#include "parka/ast/bitwise_and_expression.hpp"
#include "parka/node/node_bank.hpp"
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

		auto expression = BitwiseXorExpression(*lhs, *rhs);
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
