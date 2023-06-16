#include "parka/ast/TypeAnnotation.hpp"
#include "parka/log/Log.hpp"
#include "parka/ast/Function.hpp"
#include "parka/ast/QualifiedIdentifier.hpp"

#include "parka/util/Print.hpp"

namespace parka
{
	Optional<TypeAnnotationSyntax> TypeAnnotationSyntax::parse(Token& token)
	{
		auto identifier = QualifiedIdentifier::parse(token);

		if (!identifier)
			return {};

		auto annotation = TypeAnnotationSyntax(identifier->snippet(), *identifier);

		return annotation;
	}

	Optional<ValueType> TypeAnnotationSyntax::validate(SymbolTable& symbolTable) const
	{
		auto *entity = symbolTable.resolve(_identifier);

		if (!entity)
			return {};

		auto valueType = ValueType(*entity);

		return valueType;
	}
}
