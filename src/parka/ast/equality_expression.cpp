#include "parka/ast/equality_expression.hpp"
#include "parka/ast/relational_expression.hpp"
#include "parka/node/node_bank.hpp"
#include "parka/util/print.hpp"

Optional<EqualityType> getEqualityType(Token& token)
{
	switch (token.type())
	{
		case TokenType::Equals:
			return EQUALITY_EQUALS;

		case TokenType::NotEquals:
			return EQUALITY_NOT_EQUALS;

		default:
			return {};
	}
}

Optional<ExpressionId> EqualityExpression::parse(Token& token)
{
	auto lhs = RelationalExpression::parse(token);

	if (!lhs)
		return {};

	auto type = getEqualityType(token);

	while (type)
	{
		token.increment();

		auto rhs = RelationalExpression::parse(token);

		if (!rhs)
			return {};

		auto expression = EqualityExpression(*lhs, *rhs, *type);
		auto id = NodeBank::add(std::move(expression));

		lhs = std::move(id);
		type = getEqualityType(token);
	}

	return lhs;
}

bool EqualityExpression::validate(const EntityId&)
{
	exitNotImplemented(here());
}

Optional<Type> EqualityExpression::getType() const
{
	exitNotImplemented(here());
}
