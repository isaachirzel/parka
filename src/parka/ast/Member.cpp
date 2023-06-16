#include "parka/ast/Member.hpp"
#include "parka/ir/Member.hpp"
#include "parka/log/Log.hpp"
#include "parka/ast/Identifier.hpp"
#include "parka/ast/Keyword.hpp"
#include "parka/ast/TypeAnnotation.hpp"
#include "parka/util/Print.hpp"

namespace parka::ast
{
	static bool parsePublicity(Token& token)
	{
		auto keywordType = KeywordAst::getKeywordType(token);

		if (keywordType == KeywordType::Public)
		{
			token.increment();
			return true;
		}

		if (keywordType == KeywordType::Private)
			token.increment();
		
		return false;
	}

	MemberAst *MemberAst::parse(Token& token)
	{
		auto first = Snippet(token);
		bool isPublic = parsePublicity(token);

		auto identifier = Identifier::parse(token);

		if (!identifier)
			return {};

		if (token.type() != TokenType::Colon)
		{
			log::parseError(token, "':''", "ValueType annotations are required for member declarations.");
			return {};
		}
		
		token.increment();

		auto annotation = TypeAnnotationAst::parse(token);

		if (!annotation)
			return {};
			
		auto snippet = first + annotation->snippet();
		auto *syntax = new MemberAst(snippet, *identifier, *annotation, isPublic);

		return syntax;
	}

	bool MemberAst::declareSelf(SymbolTable& parent)
	{
		_parent = &parent;

		return parent.declare(*this);
	}

	ir::MemberIr *MemberAst::validate()
	{
		log::notImplemented(here());
	}

	String MemberAst::getSymbol() const
	{
		// TODO: Differentiate between static and regular

		return name();
	}
}
