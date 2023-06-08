#include "parka/syntax/VariableSyntax.hpp"
#include "parka/symbol/Identifier.hpp"
#include "parka/syntax/KeywordSyntax.hpp"
#include "parka/syntax/TypeAnnotationSyntax.hpp"

#include "parka/util/Print.hpp"

namespace parka
{
	const VariableSyntax *VariableSyntax::parse(Token& token)
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
		auto& syntax = EntitySyntax::create(std::move(variable));

		return (const VariableSyntax*)&syntax;
	}

	// bool VariableSyntax::validate(const EntitySyntax& function)
	// {
	// 	_isValidated = true;

	// 	if (_annotation)
	// 	{
	// 		if (!_annotation->validate(function))
	// 			return false;

	// 		auto type = _annotation->getType();

	// 		_type = type;
	// 	}

	// 	return true;
	// }

	// Optional<ValueType> VariableSyntax::getType() const
	// {
	// 	if (!_type)
	// 		return {};

	// 	return *_type;
	// }
}
