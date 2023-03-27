#include "parka/ast/expression/bitwise_and.hpp"
#include "parka/ast/expression/equality.hpp"
#include "parka/ast/expression/expression.hpp"
#include "parka/entity/node_bank.hpp"
#include "parka/token.hpp"
#include "parka/util/optional.hpp"

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

		auto expression = BitwiseAndExpression(lhs.unwrap(), rhs.unwrap());
		auto id = NodeBank::add(std::move(expression));

		lhs = std::move(id);
	}

	return lhs;
}
