#include "parka/ast/member.hpp"

#include "parka/ast/type_annotation.hpp"

#include "parka/util/print.hpp"

bool parsePublicity(Token& token)
{
	if (token.type() == TokenType::KeywordPublic)
	{
		token.increment();
		return true;
	}

	if (token.type() == TokenType::KeywordPrivate)
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

bool Member::validate(SymbolTable& symbols)
{
	return _annotation.validate(symbols);
}
