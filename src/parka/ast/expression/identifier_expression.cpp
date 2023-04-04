#include "parka/ast/expression/identifier_expression.hpp"
#include "parka/ast/function/function.hpp"
#include "parka/symbol/node_bank.hpp"
#include "parka/token.hpp"
#include "parka/util/array.hpp"
#include "parka/util/print.hpp"
#include "parka/util/optional.hpp"

Optional<ExpressionId> IdentifierExpression::parse(Token& token)
{
	auto identifier = QualifiedIdentifier::parse(token);
	auto expression = IdentifierExpression(identifier.unwrap());
	auto id = NodeBank::add(std::move(expression));

	token.increment();

	return id;
}

bool IdentifierExpression::validate(const EntityId& functionId)
{
	auto& function = NodeBank::getFunction(functionId);
	auto entity = function.resolve(_identifier);

	if (!entity)
		return false;

	_entityId = entity.unwrap();

	return true;
}

Optional<Type> IdentifierExpression::getType(Ref<Type>) const
{
	if (_entityId)
		return Type(*_entityId);

	return {};
}
