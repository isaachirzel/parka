#include "parka/ast/member_access_expression.hpp"
#include "parka/ast/expression.hpp"
#include "parka/node/node_bank.hpp"
#include "parka/util/print.hpp"

Optional<ExpressionId> MemberAccess::parse(Token& token, ExpressionId primary)
{
	if (token.type() != TokenType::Dot)
	{
		printParseError(token, "'.'");
		return {};
	}

	token.increment();
	
	if (token.type() != TokenType::Identifier)
	{
		printParseError(token, "member, method, or property name");
		return {};
	}

	auto expression = MemberAccess(std::move(primary), token);
	auto id = NodeBank::add(std::move(expression));

	token.increment();

	return id;
}

bool MemberAccess::validate(const EntityId&)
{
	exitNotImplemented(here());
}

Optional<Type> MemberAccess::getType() const
{
	exitNotImplemented(here());
}
