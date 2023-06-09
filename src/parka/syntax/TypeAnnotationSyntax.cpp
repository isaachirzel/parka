#include "parka/syntax/TypeAnnotationSyntax.hpp"
#include "parka/syntax/FunctionSyntax.hpp"
#include "parka/symbol/QualifiedIdentifier.hpp"

#include "parka/util/Print.hpp"

namespace parka
{
	TypeAnnotationSyntax::TypeAnnotationSyntax(QualifiedIdentifier&& identifier) :
	_identifier(std::move(identifier))
	{}

	Optional<TypeAnnotationSyntax> TypeAnnotationSyntax::parse(Token& token)
	{
		auto identifier = QualifiedIdentifier::parse(token);

		if (!identifier)
			return {};

		auto annotation = TypeAnnotationSyntax(*identifier);

		return annotation;
	}

	// bool TypeAnnotationSyntax::validate(const EntitySyntax& function)
	// {
	// 	auto& function = SyntaxRepository::getFunction(function);
	// 	auto entity = function.resolve(_identifier);

	// 	if (!entity)
	// 		return false;

	// 	_type = ValueType(*entity);

	// 	return true;
	// }
}
