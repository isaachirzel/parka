#include "parka/ast/Parameter.hpp"
#include "parka/log/Log.hpp"
#include "parka/ast/Identifier.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/ast/Keyword.hpp"
#include "parka/ast/TypeAnnotation.hpp"

#include "parka/util/Print.hpp"

namespace parka
{
	ParameterSyntax *ParameterSyntax::parse(Token& token)
	{
		auto first = Snippet(token);
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

		auto snippet = first + annotation->snippet();
		auto *syntax = new ParameterSyntax(snippet, *identifier, *annotation, isMutable);
		
		return syntax;
	}

	ParameterContext *ParameterSyntax::validate(SymbolTable& symbolTable)
	{
		auto isDeclared = _parent->declare(*this);
		auto valueType = _annotation.validate(symbolTable);

		if (!isDeclared || !valueType)
			return nullptr;

		auto *context = new ParameterContext(*valueType);

		return context;
	}

	String ParameterSyntax::getSymbol() const
	{
		return name();
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
