#include "parka/ast/type/type_annotation.hpp"
#include "parka/symbol/node_bank.hpp"
#include "parka/util/print.hpp"

Optional<TypeAnnotation> TypeAnnotation::parse(Token& token)
{
	if (token.type() != TokenType::Identifier)
	{
		printParseError(token, "type annotation");
		return {};
	}
	
	auto annotation = TypeAnnotation(token);

	token.increment();

	return annotation;
}

bool TypeAnnotation::validate(LocalSymbolTable& symbols)
{
	auto entityId = symbols.resolve(_token);

	if (!entityId)
		return false;

	_type = Type(*entityId);

	return true;
}
