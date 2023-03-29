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
	exitNotImplemented(here());
	// auto context = symbols.resolve(_token);

	// if (!context)
	// 	return false;

	// _entityId = EntityId(context->id());

	// return true;
}

Optional<Type> Identifier::getType(const SymbolTable& symbols, Ref<Type> expected) const
{
	if (_entityId)
		return Type(*_entityId);

	return {};
}
