#include "parka/ast/TypeAnnotation.hpp"
#include "parka/log/Log.hpp"
#include "parka/ast/Function.hpp"
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
		auto *entity = symbolTable.resolve(_identifier);

		if (!entity)
			return {};

		auto *context = entity->context();

		if (!context)
			return {};

		auto valueType = ValueType(*context);

		return valueType;
	}
}
