#include "parka/ast/identifier_expression.hpp"
#include "parka/ast/function.hpp"
#include "parka/node/node_bank.hpp"
#include "parka/node/typed_entity.hpp"
#include "parka/token.hpp"
#include "parka/util/array.hpp"
#include "parka/util/print.hpp"
#include "parka/util/optional.hpp"

Optional<ExpressionId> IdentifierExpression::parse(Token& token)
{
	auto identifier = QualifiedIdentifier::parse(token);
	auto expression = IdentifierExpression(*identifier);
	auto id = NodeBank::add(std::move(expression));

	return id;
}

bool IdentifierExpression::validate(const EntityId& functionId)
{
	print("Validate identifier");
	auto& function = NodeBank::getFunction(functionId);
	auto entityId = function.resolve(_identifier);

	if (!entityId)
		return false;

	_entityId = *entityId;

	return true;
}

Optional<Type> IdentifierExpression::getType() const
{
	auto& entity = NodeBank::get(*_entityId);
	auto *typedEntity = dynamic_cast<TypedEntity*>(&entity);

	if (typedEntity == nullptr)
	{
		printError("Unable to get type of $ `$`.", entity.type(), entity.identifier());
		return {};
	}

	auto type = typedEntity->getType();

	return type;
}
