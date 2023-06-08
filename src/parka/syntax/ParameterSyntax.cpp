#include "parka/syntax/ParameterSyntax.hpp"
#include "parka/log/Log.hpp"
#include "parka/symbol/Identifier.hpp"
#include "parka/syntax/KeywordSyntax.hpp"
#include "parka/syntax/TypeAnnotationSyntax.hpp"

#include "parka/util/Print.hpp"

namespace parka
{
	const ParameterSyntax *ParameterSyntax::parse(Token& token)
	{
		auto mutKeyword = KeywordSyntax::parseMut(token);
		auto isMutable = !!mutKeyword;
		auto identifier = Identifier::parse(token);

		if (!identifier)
			return {};

		if (token.type() != TokenType::Colon)
		{
			log::parseError(token, "':'", "Parameters require a type annotation.");
			return {};
		}

		token.increment();

		auto annotation = TypeAnnotationSyntax::parse(token);

		if (!annotation)
			return {};
		
		auto parameter = ParameterSyntax(*identifier, *annotation, isMutable);
		auto& syntax = EntitySyntax::create(std::move(parameter));
		
		return (const ParameterSyntax*)&syntax;
	}

	// bool ParameterSyntax::validate(const EntitySyntax& function)
	// {
	// 	auto success = true;

	// 	if (!_annotation.validate(function))
	// 		success = false;

	// 	return success;
	// }

	// Optional<ValueType> ParameterSyntax::getType() const
	// {
	// 	if (!_type)
	// 		return {};

	// 	return *_type;
	// }
}
