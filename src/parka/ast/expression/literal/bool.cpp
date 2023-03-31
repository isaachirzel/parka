#include "parka/ast/expression/literal/bool.hpp"
#include "parka/symbol/node_bank.hpp"
#include "parka/util/print.hpp"

Optional<bool> parseBool(Token& token)
{
	switch (token.type())
	{
		case TokenType::KeywordTrue:
			return true;

		case TokenType::KeywordFalse:
			return false;

		default:
			printParseError(token, "`true` or `false`");
			return {};
	}
}

Optional<ExpressionId> BoolLiteral::parse(Token& token)
{
	auto value = parseBool(token);

	if (!value)
		return {};

	auto literal = BoolLiteral(token, *value);
	auto id = NodeBank::add(std::move(literal));

	token.increment();

	return id;
}


bool BoolLiteral::validate(LocalSymbolTable& symbols)
{
	exitNotImplemented(here());
}

Optional<Type> BoolLiteral::getType(const LocalSymbolTable& symbolTable, Ref<Type> expected) const
{
	exitNotImplemented(here());
}

