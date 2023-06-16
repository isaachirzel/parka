#include "parka/ast/Parameter.hpp"
#include "parka/ir/Parameter.hpp"
#include "parka/log/Log.hpp"
#include "parka/ast/Identifier.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/ast/Keyword.hpp"
#include "parka/ast/TypeAnnotation.hpp"

#include "parka/util/Print.hpp"

namespace parka::ast
{
	ParameterAst *ParameterAst::parse(Token& token)
	{
		auto first = Snippet(token);
		auto mutKeyword = KeywordAst::parseMut(token);
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

		auto annotation = TypeAnnotationAst::parse(token);

		if (!annotation)
			return {};

		auto snippet = first + annotation->snippet();
		auto *syntax = new ParameterAst(snippet, *identifier, *annotation, isMutable);
		
		return syntax;
	}

	ir::ParameterIr *ParameterAst::validate(SymbolTable& symbolTable)
	{
		auto isDeclared = _parent->declare(*this);
		auto valueType = _annotation.validate(symbolTable);

		if (!isDeclared || !valueType)
			return nullptr;

		auto *context = new ir::ParameterIr(*valueType);

		return context;
	}

	String ParameterAst::getSymbol() const
	{
		return name();
	}

	std::ostream& operator<<(std::ostream& out, const ParameterAst& syntax)
	{
		if (syntax._isMutable)
			out << "mut ";

		out << syntax._identifier;
		// TODO: Add annotation

		return out;
	}
}
