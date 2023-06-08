#include "parka/syntax/IdentifierExpressionSyntax.hpp"
#include "parka/syntax/FunctionSyntax.hpp"

#include "parka/Token.hpp"
#include "parka/util/Array.hpp"
#include "parka/util/Print.hpp"
#include "parka/util/Optional.hpp"

namespace parka
{
	const IdentifierExpressionSyntax *IdentifierExpressionSyntax::parse(Token& token)
	{
		auto identifier = QualifiedIdentifier::parse(token);
		auto expression = IdentifierExpressionSyntax(*identifier);
		auto& syntax = ExpressionSyntax::create(std::move(expression));

		return (const IdentifierExpressionSyntax*)&syntax;
	}

	// bool IdentifierExpressionSyntax::validate(const EntitySyntax& function)
	// {
	// 	print("Validate identifier");
	// 	auto& function = SyntaxRepository::getFunction(function);
	// 	auto entity = function.resolve(_identifier);

	// 	if (!entity)
	// 		return false;

	// 	_entity = *entity;

	// 	return true;
	// }

	// Optional<ValueType> IdentifierExpressionSyntax::getType() const
	// {
	// 	auto& entity = SyntaxRepository::get(*_entity);
	// 	auto *typedEntity = dynamic_cast<TypedEntity*>(&entity);

	// 	if (typedEntity == nullptr)
	// 	{
	// 		log::error("Unable to get type of $ `$`.", entity.type(), entity.identifier());
	// 		return {};
	// 	}

	// 	auto type = typedEntity->getType();

	// 	return type;
	// }
}
