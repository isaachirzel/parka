#include "parka/ast/boolean_and_expression.hpp"
#include "parka/ast/bitwise_or_expression.hpp"
#include "parka/ast/expression.hpp"
#include "parka/node/node_bank.hpp"
#include "parka/util/print.hpp"


Optional<ExpressionId> BooleanAndExpression::parse(Token& token)
{
	auto lhs = BitwiseOrExpression::parse(token);

	if (!lhs)
		return {};

	while (token.type() == TokenType::BooleanAnd)
	{
		token.increment();

		auto rhs = BitwiseOrExpression::parse(token);

		if (!rhs)
			return {};

		auto expression = BooleanAndExpression(*lhs, *rhs);
		auto id = NodeBank::add(std::move(expression));

		lhs = std::move(id);
	}

	return lhs;
}

bool BooleanAndExpression::validate(const EntityId&)
{
	exitNotImplemented(here());
}

Optional<Type> BooleanAndExpression::getType() const
{
	exitNotImplemented(here());
}
