#include "parka/ast/expression/member_access.hpp"
#include "parka/ast/expression/expression.hpp"
#include "parka/entity/node_bank.hpp"
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
