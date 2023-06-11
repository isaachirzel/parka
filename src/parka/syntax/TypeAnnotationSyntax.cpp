#include "parka/syntax/TypeAnnotationSyntax.hpp"
#include "parka/log/Log.hpp"
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

	Optional<ValueType> TypeAnnotationSyntax::validate(SymbolTable& symbolTable) const
	{
		log::notImplemented(here());
	}
}
