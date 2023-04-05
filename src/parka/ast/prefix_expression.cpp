
#include "parka/ast/prefix_expression.hpp"
#include "parka/ast/expression.hpp"
#include "parka/ast/postfix_expression.hpp"

#include "parka/ast/primary_expression.hpp"
#include "parka/node/node_bank.hpp"
#include "parka/util/print.hpp"

Optional<PrefixType> parsePrefixType(Token& token)
{
	switch (token.type())
	{
		case TokenType::Ampersand:
			return PrefixType::Reference;

		case TokenType::Asterisk:
			return PrefixType::Dereference;

		case TokenType::Plus:
			return PrefixType::Positive;

		case TokenType::Minus:
			return PrefixType::Negative;

		case TokenType::BitwiseNot:
			return PrefixType::BitwiseNot;

		case TokenType::BooleanNot:
			return PrefixType::BooleanNot;

		default:
			return {};
	}
}

Optional<ExpressionId> Prefix::parse(Token& token)
{
	auto type = parsePrefixType(token);

	if (!type)
		return PrimaryExpression::parse(token);

	auto prefixToken = token;

	token.increment();

	auto inner = Prefix::parse(token);
	auto expression = Prefix(*type, *inner, prefixToken);
	auto id = NodeBank::add(std::move(expression));

	return id;
}

bool Prefix::validate(const EntityId&)
{
	exitNotImplemented(here());
}

Optional<Type> Prefix::getType() const
{
	exitNotImplemented(here());
}
