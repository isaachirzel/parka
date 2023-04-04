#include "parka/ast/keyword.hpp"
#include "parka/util/optional.hpp"
#include "parka/util/print.hpp"
#include "parka/util/string.hpp"
#include "parka/util/table.hpp"

const Table<String, KeywordType> keywords =
{
	{ "break", KeywordType::Break },
	{ "case", KeywordType::Case },
	{ "continue", KeywordType::Continue },
	{ "yield", KeywordType::Yield },
	{ "else", KeywordType::Else },
	{ "enum", KeywordType::Enum },
	{ "import", KeywordType::Import },
	{ "export", KeywordType::Export },
	{ "false", KeywordType::False },
	{ "for", KeywordType::For },
	{ "function", KeywordType::Function },
	{ "operator", KeywordType::Operator },
	{ "if", KeywordType::If },
	{ "loop", KeywordType::Loop },
	{ "match", KeywordType::Match },
	{ "mut", KeywordType::Mut },
	{ "return", KeywordType::Return },
	{ "struct", KeywordType::Struct },
	{ "then", KeywordType::Then },
	{ "true", KeywordType::True },
	{ "type", KeywordType::Type },
	{ "private", KeywordType::Private },
	{ "public", KeywordType::Public },
	{ "var", KeywordType::Var },
	{ "while", KeywordType::While }
};

KeywordType Keyword::getKeywordType(const Token& token)
{
	if (token.type() != TokenType::Identifier)
		return {};

	auto text = token.text();
	auto iter = keywords.find(text);

	if (iter == keywords.end())
		return KeywordType::None;

	return iter->second;
}

Optional<Keyword> Keyword::parseBool(Token& token)
{
	auto type = getKeywordType(token);

	if (type != KeywordType::True && type != KeywordType::False)
	{
		printParseError(token, "`true` or `false`");
		return {};
	}

	auto keyword = Keyword(token, type);

	token.increment();
	
	return keyword;
}

Optional<Keyword> Keyword::parseStruct(Token& token)
{
	auto type = getKeywordType(token);

	if (type != KeywordType::Struct)
	{
		printParseError(token, "`struct` keyword");
		return {};
	}

	auto keyword = Keyword(token, type);

	token.increment();

	return keyword;
}

Optional<Keyword> Keyword::parseVar(Token& token)
{
	auto type = getKeywordType(token);

	if (type != KeywordType::Var)
	{
		printParseError(token, "`var` keyword");
		return {};
	}

	auto keyword = Keyword(token, type);

	token.increment();

	return keyword;
}

Optional<Keyword> Keyword::parseFunction(Token &token)
{
	auto type = getKeywordType(token);

	if (type != KeywordType::Function)
	{
		printParseError(token, "`function`");
		return {};
	}

	auto keyword = Keyword(token, type);

	token.increment();
	
	return keyword;
}

Optional<Keyword> Keyword::parseOperator(Token &token)
{
	auto type = getKeywordType(token);

	if (type != KeywordType::Operator)
	{
		printParseError(token, "`operator`");
		return {};
	}

	auto keyword = Keyword(token, type);

	token.increment();

	return keyword;
}

Optional<Keyword> Keyword::parseMut(Token &token)
{
	auto type = getKeywordType(token);

	if (type != KeywordType::Mut)
		return {};

	auto keyword = Keyword(token, type);

	token.increment();

	return keyword;
}
