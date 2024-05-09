#include "parka/ast/KeywordAst.hpp"
#include "parka/enum/KeywordType.hpp"
#include "parka/log/Log.hpp"
#include "parka/util/Result.hpp"
#include "parka/util/Print.hpp"
#include "parka/util/String.hpp"
#include "parka/util/Table.hpp"

namespace parka::ast
{
	const Table<String, KeywordType> KeywordAst::keywords = initKeywords();

	Table<String, KeywordType> KeywordAst::initKeywords()
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
		keywords.insert("struct", KeywordType::StructAst);
		keywords.insert("then", KeywordType::Then);
		keywords.insert("true", KeywordType::True);
		keywords.insert("type", KeywordType::Type);
		keywords.insert("private", KeywordType::Private);
		keywords.insert("public", KeywordType::Public);
		keywords.insert("var", KeywordType::Var);
		keywords.insert("while", KeywordType::While);

		return keywords;
	}

	KeywordType KeywordAst::getKeywordType(const String& text)
	{
		const auto *keywordType = keywords.find(text);

		if (!keywordType)
			return KeywordType::None;

		return *keywordType;
	}

	Result<KeywordAst> KeywordAst::parseBoolKeyword(Token& token)
	{
		auto type = getKeywordType(token.text());

		if (type != KeywordType::True && type != KeywordType::False)
		{
			log::parseError(token, "`true` or `false`");
			return {};
		}

		auto keyword = KeywordAst(token, type);

		token.increment();
		
		return keyword;
	}

	Result<KeywordAst> KeywordAst::parseStructKeyword(Token& token)
	{
		auto type = getKeywordType(token.text());

		if (type != KeywordType::StructAst)
		{
			log::parseError(token, "`struct` keyword");
			return {};
		}

		auto keyword = KeywordAst(token, type);

		token.increment();

		return keyword;
	}

	Result<KeywordAst> KeywordAst::parseVarKeyword(Token& token)
	{
		auto type = getKeywordType(token.text());

		if (type != KeywordType::Var)
		{
			log::parseError(token, "`var` keyword");
			return {};
		}

		auto keyword = KeywordAst(token, type);

		token.increment();

		return keyword;
	}

	Result<KeywordAst> KeywordAst::parseFunctionKeyword(Token &token)
	{
		auto type = getKeywordType(token.text());

		if (type != KeywordType::Function)
		{
			log::parseError(token, "`function`");
			return {};
		}

		auto keyword = KeywordAst(token, type);

		token.increment();
		
		return keyword;
	}

	Result<KeywordAst> KeywordAst::parseOperatorKeyword(Token &token)
	{
		auto type = getKeywordType(token.text());

		if (type != KeywordType::Operator)
		{
			log::parseError(token, "`operator`");
			return {};
		}

		auto keyword = KeywordAst(token, type);

		token.increment();

		return keyword;
	}

	Result<KeywordAst> KeywordAst::parseMutKeyword(Token &token)
	{
		auto type = getKeywordType(token.text());

		if (type != KeywordType::Mut)
			return {};

		auto keyword = KeywordAst(token, type);

		token.increment();

		return keyword;
	}
}
