#include "parka/ast/type_annotation.hpp"
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
