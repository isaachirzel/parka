#include "parka/syntax/TypeAnnotationSyntax.hpp"
#include "parka/syntax/FunctionSyntax.hpp"
#include "parka/symbol/QualifiedIdentifier.hpp"
#include "parka/Storage.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	Optional<TypeAnnotationSyntax> TypeAnnotationSyntax::parse(Token& token)
	{
		auto identifier = QualifiedIdentifier::parse(token);

		if (!identifier)
			return {};

		auto annotation = TypeAnnotationSyntax(*identifier);

		return annotation;
	}

	// bool TypeAnnotationSyntax::validate(const EntityId& functionId)
	// {
	// 	auto& function = Storage::getFunction(functionId);
	// 	auto entityId = function.resolve(_identifier);

	// 	if (!entityId)
	// 		return false;

	// 	_type = Type(*entityId);

	// 	return true;
	// }
}
