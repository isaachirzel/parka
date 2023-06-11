#include "parka/syntax/ParameterSyntax.hpp"
#include "parka/log/Log.hpp"
#include "parka/symbol/Identifier.hpp"
#include "parka/syntax/KeywordSyntax.hpp"
#include "parka/syntax/TypeAnnotationSyntax.hpp"

#include "parka/util/Print.hpp"

namespace parka
{
	ParameterSyntax::ParameterSyntax(Identifier&& identifier, TypeAnnotationSyntax&& annotation, bool isMutable) :
	_identifier(std::move(identifier)),
	_annotation(std::move(annotation)),
	_isMutable(isMutable)
	{}

	ParameterContext *ParameterSyntax::validate(FunctionSymbolTable& symbolTable)
	{
		log::notImplemented(here());
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
