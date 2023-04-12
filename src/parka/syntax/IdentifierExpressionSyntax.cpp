#include "parka/syntax/IdentifierExpressionSyntax.hpp"
#include "parka/syntax/FunctionSyntax.hpp"
#include "parka/repository/SyntaxRepository.hpp"
#include "parka/Token.hpp"
#include "parka/util/Array.hpp"
#include "parka/util/Print.hpp"
#include "parka/util/Optional.hpp"

namespace parka
{
	Optional<ExpressionSyntaxId> IdentifierExpressionSyntax::parse(Token& token)
	{
		auto identifier = QualifiedIdentifier::parse(token);
		auto expression = IdentifierExpressionSyntax(*identifier);
		auto id = SyntaxRepository::add(std::move(expression));

		return id;
	}

	// bool IdentifierExpressionSyntax::validate(const EntitySyntaxId& functionId)
	// {
	// 	print("Validate identifier");
	// 	auto& function = SyntaxRepository::getFunction(functionId);
	// 	auto entityId = function.resolve(_identifier);

	// 	if (!entityId)
	// 		return false;

	// 	_entityId = *entityId;

	// 	return true;
	// }

	// Optional<Type> IdentifierExpressionSyntax::getType() const
	// {
	// 	auto& entity = SyntaxRepository::get(*_entityId);
	// 	auto *typedEntity = dynamic_cast<TypedEntity*>(&entity);

	// 	if (typedEntity == nullptr)
	// 	{
	// 		printError("Unable to get type of $ `$`.", entity.type(), entity.identifier());
	// 		return {};
	// 	}

	// 	auto type = typedEntity->getType();

	// 	return type;
	// }
}
