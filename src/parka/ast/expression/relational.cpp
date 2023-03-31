#include "parka/ast/expression/relational.hpp"
#include "parka/ast/expression/shift.hpp"
#include "parka/symbol/node_bank.hpp"
#include "parka/util/print.hpp"

Optional<RelationalType> parseRelationalType(Token& token)
{
	switch (token.type())
	{
		case TokenType::GreaterThan:
			return RelationalType::GreaterThan;

		case TokenType::LessThan:
			return RelationalType::LessThan;

		case TokenType::GreaterThanOrEqualTo:
			return RelationalType::GreaterThanOrEqualTo;

		case TokenType::LessThanOrEqualTo:
			return RelationalType::LessThanOrEqualTo;

		default:
			return {};
	}
}

Optional<ExpressionId> RelationalExpression::parse(Token& token)
{
	auto lhs = BitShiftExpression::parse(token);

	if (!lhs)
		return {};

	auto type = parseRelationalType(token);

	while (type)
	{
		token.increment();

		auto rhs = BitShiftExpression::parse(token);

		if (!rhs)
			return {};

		auto expression = RelationalExpression(lhs.unwrap(), rhs.unwrap(), type.unwrap());
		auto id = NodeBank::add(std::move(expression));

		lhs = std::move(id);
		type = parseRelationalType(token);
	}

	return lhs;
}

bool RelationalExpression::validate(LocalSymbolTable& symbols)
{
	exitNotImplemented(here());
}

Optional<Type> RelationalExpression::getType(const LocalSymbolTable& symbolTable, Ref<Type> expected) const
{
	exitNotImplemented(here());
}
