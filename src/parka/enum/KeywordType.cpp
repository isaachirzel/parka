#include "parka/enum/KeywordType.hpp"
#include "parka/util/Table.hpp"

namespace parka
{
	static Table<String, KeywordType> initKeywords()
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
		keywords.insert("in", KeywordType::In);
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

	const Table<String, KeywordType> keywords = initKeywords();

	KeywordType toKeywordType(const String& text)
	{
		const auto *keywordType = keywords.find(text);

		if (!keywordType)
			return KeywordType::None;

		return *keywordType;
	}
}
