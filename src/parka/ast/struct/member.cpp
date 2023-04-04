#include "parka/ast/struct/member.hpp"

#include "parka/ast/keyword.hpp"
#include "parka/ast/type/type_annotation.hpp"

#include "parka/util/print.hpp"

bool parsePublicity(Token& token)
{
	auto keywordType = Keyword::getKeywordType(token);

	if (keywordType == KeywordType::Public)
	{
		token.increment();
		return true;
	}

	if (keywordType == KeywordType::Private)
		token.increment();
	
	return false;
}

Optional<Member> Member::parse(Token& token)
{
	bool isPublic = parsePublicity(token);

	if (token.type() != TokenType::Identifier)
	{
		printParseError(token, "member name");
		return {};
	}

	auto name = token;

	token.increment();

	if (token.type() != TokenType::Colon)
	{
		printParseError(token, "':''", "Type annotations are required for member declarations.");
		return {};
	}
	
	token.increment();

	auto annotation = TypeAnnotation::parse(token);

	if (!annotation)
		return {};

	auto member = Member(name, name.text(), annotation.unwrap(), isPublic);

	return member;
}

bool Member::validate(const EntityId& functionId)
{
	return _annotation.validate(functionId);
}
