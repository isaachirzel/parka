#include "parka/syntax/MemberSyntax.hpp"
#include "parka/log/Log.hpp"
#include "parka/symbol/StructSymbolTable.hpp"
#include "parka/syntax/KeywordSyntax.hpp"
#include "parka/syntax/TypeAnnotationSyntax.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	MemberSyntax::MemberSyntax(const Token& name, String&& symbol, TypeAnnotationSyntax&& annotation, bool isPublic) :
	_name(name),
	_symbol(std::move(symbol)),
	_annotation(std::move(annotation)),
	_isPublic(isPublic)
	{}

	static bool parsePublicity(Token& token)
	{
		auto keywordType = KeywordSyntax::getKeywordType(token);

		if (keywordType == KeywordType::Public)
		{
			token.increment();
			return true;
		}

		if (keywordType == KeywordType::Private)
			token.increment();
		
		return false;
	}

	Optional<MemberSyntax> MemberSyntax::parse(Token& token)
	{
		bool isPublic = parsePublicity(token);

		if (token.type() != TokenType::Identifier)
		{
			log::parseError(token, "member name");
			return {};
		}

		auto name = token;

		token.increment();

		if (token.type() != TokenType::Colon)
		{
			log::parseError(token, "':''", "ValueType annotations are required for member declarations.");
			return {};
		}
		
		token.increment();

		auto annotation = TypeAnnotationSyntax::parse(token);

		if (!annotation)
			return {};

		auto syntax = MemberSyntax(name, name.text(), *annotation, isPublic);

		return syntax;
	}

	Optional<MemberSyntax> MemberSyntax::validate(SymbolTable& symbolTable) const
	{
		log::notImplemented(here());
	}
}
