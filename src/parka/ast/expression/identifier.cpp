#include "parka/ast/expression/identifier.hpp"
#include "parka/ast/expression/expression.hpp"
#include "parka/ast/parameter.hpp"
#include "parka/ast/variable.hpp"
#include "parka/entity_context.hpp"
#include "parka/symbol.hpp"
#include "parka/symbol_table.hpp"

#include "parka/util/print.hpp"
#include "parka/util/optional.hpp"

Optional<Box<Expression>> Identifier::parse(Token& token)
{
	if (token.type() != TokenType::Identifier)
	{
		printParseError(token, "identifier");
		return {};
	}

	auto *expression = new Identifier(token);
	auto box = Box<Expression>(expression);

	token.increment();

	return box;
}

bool Identifier::validate(SymbolTable& symbols)
{
	auto context = symbols.resolve(_token);

	if (!context)
		return false;

	_entityId = EntityId(context->entityId());

	return true;
}

Optional<Type> Identifier::getType(const SymbolTable& symbols, Ref<Type> expected) const
{
	if (_entityId)
		return Type(_entityId.value());

	return {};
}
