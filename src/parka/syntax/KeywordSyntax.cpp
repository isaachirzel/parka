#include "parka/syntax/KeywordSyntax.hpp"
#include "parka/util/Optional.hpp"
#include "parka/util/Print.hpp"
#include "parka/util/String.hpp"
#include "parka/util/Table.hpp"

namespace parka
{
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
		{ "struct", KeywordType::StructSyntax },
		{ "then", KeywordType::Then },
		{ "true", KeywordType::True },
		{ "type", KeywordType::Type },
		{ "private", KeywordType::Private },
		{ "public", KeywordType::Public },
		{ "var", KeywordType::Var },
		{ "while", KeywordType::While }
	};

	KeywordType KeywordSyntax::getKeywordType(const Token& token)
	{
		if (token.type() != TokenType::Identifier)
			return {};

		auto text = token.text();
		auto iter = keywords.find(text);

		if (iter == keywords.end())
			return KeywordType::None;

		return iter->second;
	}

	Optional<KeywordSyntax> KeywordSyntax::parseBool(Token& token)
	{
		auto type = getKeywordType(token);

		if (type != KeywordType::True && type != KeywordType::False)
		{
			printParseError(token, "`true` or `false`");
			return {};
		}

		auto keyword = KeywordSyntax(token, type);

		token.increment();
		
		return keyword;
	}

	Optional<KeywordSyntax> KeywordSyntax::parseStruct(Token& token)
	{
		auto type = getKeywordType(token);

		if (type != KeywordType::StructSyntax)
		{
			printParseError(token, "`struct` keyword");
			return {};
		}

		auto keyword = KeywordSyntax(token, type);

		token.increment();

		return keyword;
	}

	Optional<KeywordSyntax> KeywordSyntax::parseVar(Token& token)
	{
		auto type = getKeywordType(token);

		if (type != KeywordType::Var)
		{
			printParseError(token, "`var` keyword");
			return {};
		}

		auto keyword = KeywordSyntax(token, type);

		token.increment();

		return keyword;
	}

	Optional<KeywordSyntax> KeywordSyntax::parseFunction(Token &token)
	{
		auto type = getKeywordType(token);

		if (type != KeywordType::Function)
		{
			printParseError(token, "`function`");
			return {};
		}

		auto keyword = KeywordSyntax(token, type);

		token.increment();
		
		return keyword;
	}

	Optional<KeywordSyntax> KeywordSyntax::parseOperator(Token &token)
	{
		auto type = getKeywordType(token);

		if (type != KeywordType::Operator)
		{
			printParseError(token, "`operator`");
			return {};
		}

		auto keyword = KeywordSyntax(token, type);

		token.increment();

		return keyword;
	}

	Optional<KeywordSyntax> KeywordSyntax::parseMut(Token &token)
	{
		auto type = getKeywordType(token);

		if (type != KeywordType::Mut)
			return {};

		auto keyword = KeywordSyntax(token, type);

		token.increment();

		return keyword;
	}
}
