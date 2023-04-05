#include "parka/ast/bitwise_and_expression.hpp"
#include "parka/ast/equality_expression.hpp"
#include "parka/ast/expression.hpp"
#include "parka/node/node_bank.hpp"
#include "parka/token.hpp"
#include "parka/util/optional.hpp"
#include "parka/util/print.hpp"

Optional<ExpressionId> BitwiseAndExpression::parse(Token& token)
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

		auto expression = BitwiseAndExpression(*lhs, *rhs);
		auto id = NodeBank::add(std::move(expression));

		lhs = std::move(id);
	}

	return lhs;
}

bool BitwiseAndExpression::validate(const EntityId&)
{
	exitNotImplemented(here());
}

Optional<Type> BitwiseAndExpression::getType() const
{
	exitNotImplemented(here());
}
