#include "parka/ast/boolean_or_expression.hpp"
#include "parka/ast/boolean_and_expression.hpp"
#include "parka/node/node_bank.hpp"
#include "parka/util/print.hpp"


Optional<ExpressionId> BooleanOrExpression::parse(Token& token)
{
	auto lhs = BooleanAndExpression::parse(token);

	if (!lhs)
		return {};

	while (token.type() == TokenType::BooleanOr)
	{
		token.increment();

		auto rhs = BooleanAndExpression::parse(token);

		if (!rhs)
			return {};

		auto expression = BooleanOrExpression(*lhs, *rhs);
		auto id = NodeBank::add(std::move(expression));

		lhs = std::move(id);
	}

	return lhs;
}

bool BooleanOrExpression::validate(const EntityId&)
{
	exitNotImplemented(here());
}

Optional<Type> BooleanOrExpression::getType() const
{
	exitNotImplemented(here());
}
