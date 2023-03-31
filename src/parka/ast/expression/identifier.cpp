#include "parka/ast/expression/identifier.hpp"
#include "parka/symbol/node_bank.hpp"
#include "parka/util/print.hpp"
#include "parka/util/optional.hpp"

Optional<ExpressionId> Identifier::parse(Token& token)
{
	if (token.type() != TokenType::Identifier)
	{
		printParseError(token, "identifier");
		return {};
	}

	auto expression = Identifier(token);
	auto id = NodeBank::add(std::move(expression));

	token.increment();

	return id;
}

bool Identifier::validate(SymbolTable& symbols)
{
	auto entity = symbols.resolve(_token);

	if (!entity)
		return false;

	_entityId = entity.unwrap();

	return true;
}

Optional<Type> Identifier::getType(const SymbolTable&, Ref<Type>) const
{
	if (_entityId)
		return Type(*_entityId);

	return {};
}
