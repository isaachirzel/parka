#include "parka/ast/TypeAnnotation.hpp"
#include "parka/log/Log.hpp"
#include "parka/ast/Function.hpp"
#include "parka/ast/QualifiedIdentifier.hpp"

#include "parka/util/Print.hpp"

namespace parka::ast
{
	Optional<TypeAnnotationAst> TypeAnnotationAst::parse(Token& token)
	{
		auto identifier = QualifiedIdentifier::parse(token);

		if (!identifier)
			return {};

		auto annotation = TypeAnnotationAst(identifier->snippet(), *identifier);

		return annotation;
	}

	Optional<ir::ValueType> TypeAnnotationAst::validate(SymbolTable&) const
	{
		log::notImplemented(here());
		// auto *entity = symbolTable.resolve(_identifier);

		// if (!entity)
		// 	return {};

		// auto valueType = ir::ValueType(*entity);

		// return valueType;
	}
}
