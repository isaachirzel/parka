#include "parka/ast/expression/literal/bool.hpp"
#include "parka/ast/keyword.hpp"
#include "parka/symbol/node_bank.hpp"
#include "parka/util/optional.hpp"
#include "parka/util/print.hpp"

Optional<bool> parseBool(Token& token)
{
	auto type = Keyword::getKeywordType(token);

	switch (type)
	{
		case KeywordType::True:
			return true;

		case KeywordType::False:
			return false;

		default:
			break;
	}

	printParseError(token, "`true` or `false`");
	
	return {};
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


bool BoolLiteral::validate(const EntityId&)
{
	exitNotImplemented(here());
}

Optional<Type> BoolLiteral::getType() const
{
	exitNotImplemented(here());
}

