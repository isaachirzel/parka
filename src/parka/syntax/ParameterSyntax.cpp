#include "parka/syntax/ParameterSyntax.hpp"
#include "parka/log/Log.hpp"
#include "parka/symbol/Identifier.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/syntax/KeywordSyntax.hpp"
#include "parka/syntax/TypeAnnotationSyntax.hpp"

#include "parka/util/Print.hpp"

namespace parka
{
	ParameterSyntax::ParameterSyntax(Identifier&& identifier, TypeAnnotationSyntax&& annotation, bool isMutable) :
	_identifier(std::move(identifier)),
	_annotation(std::move(annotation)),
	_parent(nullptr),
	_isMutable(isMutable)
	{}

	ParameterSyntax *ParameterSyntax::parse(Token& token)
	{
		auto mutKeyword = KeywordSyntax::parseMut(token);
		auto isMutable = !!mutKeyword;
		auto identifier = Identifier::parse(token);

		if (!identifier)
			return {};

		if (token.type() != TokenType::Colon)
		{
			log::parseError(token, "':'", "Parameters require a type annotation.");
			return {};
		}

		token.increment();

		auto annotation = TypeAnnotationSyntax::parse(token);

		if (!annotation)
			return {};
		
		auto *syntax = new ParameterSyntax(*identifier, *annotation, isMutable);
		
		return syntax;
	}

	bool ParameterSyntax::declare(SymbolTable& parent)
	{
		log::notImplemented(here());
	}

	ParameterContext *ParameterSyntax::validate()
	{
		log::notImplemented(here());
	}

	std::ostream& operator<<(std::ostream& out, const ParameterSyntax& syntax)
	{
		if (syntax._isMutable)
			out << "mut ";

		out << syntax._identifier;
		// TODO: Add annotation

		return out;
	}
}
