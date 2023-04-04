#include "parka/ast/expression/boolean_or.hpp"
#include "parka/ast/expression/boolean_and.hpp"
#include "parka/symbol/node_bank.hpp"
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

		auto expression = BooleanOrExpression(lhs.unwrap(), rhs.unwrap());
		auto id = NodeBank::add(std::move(expression));

		lhs = std::move(id);
	}

	return lhs;
}

bool BooleanOrExpression::validate(const EntityId&)
{
	exitNotImplemented(here());
}

Optional<Type> BooleanOrExpression::getType(Ref<Type>) const
{
	exitNotImplemented(here());
}
