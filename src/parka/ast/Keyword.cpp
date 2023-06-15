#include "parka/ast/Keyword.hpp"
#include "parka/enum/KeywordType.hpp"
#include "parka/log/Log.hpp"
#include "parka/util/Optional.hpp"
#include "parka/util/Print.hpp"
#include "parka/util/String.hpp"
#include "parka/util/Table.hpp"

namespace parka
{
	const Table<String, KeywordType> KeywordSyntax::keywords = initKeywords();

	Table<String, KeywordType> KeywordSyntax::initKeywords()
	{
		auto keywords = Table<String, KeywordType>(25);
			
		keywords.insert("break", KeywordType::Break);
		keywords.insert("case", KeywordType::Case);
		keywords.insert("continue", KeywordType::Continue);
		keywords.insert("yield", KeywordType::Yield);
		keywords.insert("else", KeywordType::Else);
		keywords.insert("enum", KeywordType::Enum);
		keywords.insert("import", KeywordType::Import);
		keywords.insert("export", KeywordType::Export);
		keywords.insert("false", KeywordType::False);
		keywords.insert("for", KeywordType::For);
		keywords.insert("function", KeywordType::Function);
		keywords.insert("operator", KeywordType::Operator);
		keywords.insert("if", KeywordType::If);
		keywords.insert("loop", KeywordType::Loop);
		keywords.insert("match", KeywordType::Match);
		keywords.insert("mut", KeywordType::Mut);
		keywords.insert("return", KeywordType::Return);
		keywords.insert("struct", KeywordType::StructSyntax);
		keywords.insert("then", KeywordType::Then);
		keywords.insert("true", KeywordType::True);
		keywords.insert("type", KeywordType::ValueType);
		keywords.insert("private", KeywordType::Private);
		keywords.insert("public", KeywordType::Public);
		keywords.insert("var", KeywordType::Var);
		keywords.insert("while", KeywordType::While);

		return keywords;
	}

	KeywordType KeywordSyntax::getKeywordType(const Token& token)
	{
		if (token.type() != TokenType::Identifier)
			return {};

		auto text = token.text();
		const auto *keywordType = keywords.find(text);

		if (!keywordType)
			return KeywordType::None;

		return *keywordType;
	}

	Optional<KeywordSyntax> KeywordSyntax::parseBool(Token& token)
	{
		auto type = getKeywordType(token);

		if (type != KeywordType::True && type != KeywordType::False)
		{
			log::parseError(token, "`true` or `false`");
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
			log::parseError(token, "`struct` keyword");
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
			log::parseError(token, "`var` keyword");
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
			log::parseError(token, "`function`");
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
			log::parseError(token, "`operator`");
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
