#include "parka/syntax/VariableSyntax.hpp"
#include "parka/log/Log.hpp"
#include "parka/symbol/Identifier.hpp"
#include "parka/syntax/KeywordSyntax.hpp"
#include "parka/syntax/TypeAnnotationSyntax.hpp"

#include "parka/util/Print.hpp"

namespace parka
{
	VariableSyntax::VariableSyntax(Identifier&& identifier, bool isMutable, Optional<TypeAnnotationSyntax> annotation) :
	_identifier(std::move(identifier)),
	_annotation(std::move(annotation)),
	_isMutable(isMutable)
	{}

	VariableSyntax *VariableSyntax::parse(Token& token)
	{
		// TODO: VariableSyntax mutability
		auto keyword = KeywordSyntax::parseVar(token);

		if (!keyword)
			return {};	
		
		auto identifier = Identifier::parse(token);

		if (!identifier)
			return {};

		Optional<TypeAnnotationSyntax> annotation;

		if (token.type() == TokenType::Colon)
		{
			token.increment();

			annotation = TypeAnnotationSyntax::parse(token);

			if (!annotation)
				return {};
		}

		auto *syntax = new VariableSyntax(*identifier, false, std::move(annotation));

		return syntax;
	}

	VariableContext *VariableSyntax::validate(SymbolTable& symbolTable)
	{
		if (!_annotation)
		{

		}

		log::notImplemented(here());
	}
}
