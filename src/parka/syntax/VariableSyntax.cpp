#include "parka/syntax/VariableSyntax.hpp"
#include "parka/symbol/Identifier.hpp"
#include "parka/syntax/KeywordSyntax.hpp"
#include "parka/syntax/TypeAnnotationSyntax.hpp"
#include "parka/Storage.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	Optional<EntityId> VariableSyntax::parse(Token& token)
	{
		// TODO: VariableSyntax mutability
		auto keyword = KeywordSyntax::parseVar(token);

		if (!keyword)
			return {};	
		
		auto identifier = Identifier::parse(token);

		if (!identifier)
			return {};

		Optional<TypeAnnotationSyntax> annotation;

		if (token.type() == TokenType::Colon)
		{
			token.increment();

			annotation = TypeAnnotationSyntax::parse(token);

			if (!annotation)
				return {};
		}

		auto variable = VariableSyntax(*identifier, false, std::move(annotation));
		auto id = Storage::add(std::move(variable));

		return id;
	}

	// bool VariableSyntax::validate(const EntityId& functionId)
	// {
	// 	_isValidated = true;

	// 	if (_annotation)
	// 	{
	// 		if (!_annotation->validate(functionId))
	// 			return false;

	// 		auto type = _annotation->getType();

	// 		_type = type;
	// 	}

	// 	return true;
	// }

	// Optional<Type> VariableSyntax::getType() const
	// {
	// 	if (!_type)
	// 		return {};

	// 	return *_type;
	// }
}
