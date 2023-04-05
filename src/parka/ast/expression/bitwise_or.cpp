#include "parka/ast/expression/bitwise_or.hpp"
#include "parka/ast/expression/bitwise_xor.hpp"
#include "parka/symbol/node_bank.hpp"
#include "parka/util/print.hpp"


Optional<ExpressionId> BitwiseOrExpression::parse(Token& token)
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

		auto expression = BitwiseOrExpression(lhs.unwrap(), rhs.unwrap());
		auto id = NodeBank::add(std::move(expression));

		lhs = std::move(id);
	}

	return lhs;
}

bool BitwiseOrExpression::validate(const EntityId&)
{
	exitNotImplemented(here());
}

Optional<Type> BitwiseOrExpression::getType() const
{
	exitNotImplemented(here());
}
