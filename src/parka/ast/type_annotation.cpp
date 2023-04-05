#include "parka/ast/type_annotation.hpp"
#include "parka/ast/function.hpp"
#include "parka/ast/qualified_identifier.hpp"
#include "parka/node/node_bank.hpp"
#include "parka/util/print.hpp"

Optional<TypeAnnotation> TypeAnnotation::parse(Token& token)
{
	auto identifier = QualifiedIdentifier::parse(token);

	if (!identifier)
		return {};

	auto annotation = TypeAnnotation(*identifier);

	return annotation;
}

bool TypeAnnotation::validate(const EntityId& functionId)
{
	auto& function = NodeBank::getFunction(functionId);
	auto entityId = function.resolve(_identifier);

	if (!entityId)
		return false;

	_type = Type(*entityId);

	return true;
}
