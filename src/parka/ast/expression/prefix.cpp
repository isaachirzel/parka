
#include "parka/ast/expression/prefix.hpp"
#include "parka/ast/expression/expression.hpp"
#include "parka/ast/expression/postfix.hpp"

#include "parka/ast/expression/primary.hpp"
#include "parka/symbol/node_bank.hpp"
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
	auto expression = Prefix(type.value(), inner.unwrap(), prefixToken);
	auto id = NodeBank::add(std::move(expression));

	return id;
}

bool Prefix::validate(SymbolTable& symbols)
{
	exitNotImplemented(here());
}

Optional<Type> Prefix::getType(const SymbolTable& symbolTable, Ref<Type> expected) const
{
	exitNotImplemented(here());
}
