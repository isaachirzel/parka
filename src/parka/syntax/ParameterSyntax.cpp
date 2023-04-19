#include "parka/syntax/ParameterSyntax.hpp"
#include "parka/symbol/Identifier.hpp"
#include "parka/syntax/KeywordSyntax.hpp"
#include "parka/syntax/TypeAnnotationSyntax.hpp"

#include "parka/util/Print.hpp"

namespace parka
{
	Optional<EntitySyntaxId> ParameterSyntax::parse(Token& token)
	{
		auto mutKeyword = KeywordSyntax::parseMut(token);
		auto isMutable = !!mutKeyword;

		auto identifier = Identifier::parse(token);

		if (!identifier)
			return {};

		if (token.type() != TokenType::Colon)
		{
			printParseError(token, "':'", "Parameters require a type annotation.");
			return {};
		}

		token.increment();

		auto annotation = TypeAnnotationSyntax::parse(token);

		if (!annotation)
			return {};
		
		auto parameter = ParameterSyntax(*identifier, *annotation, isMutable);
		auto id = EntitySyntaxId::create(std::move(parameter));
		
		return id;
	}

	// bool ParameterSyntax::validate(const EntitySyntaxId& functionId)
	// {
	// 	auto success = true;

	// 	if (!_annotation.validate(functionId))
	// 		success = false;

	// 	return success;
	// }

	// Optional<Type> ParameterSyntax::getType() const
	// {
	// 	if (!_type)
	// 		return {};

	// 	return *_type;
	// }
}
