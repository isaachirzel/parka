#include <warbler/lexicon/keyword.hpp>

#include <warbler/util/table.hpp>

namespace warbler::lexicon
{
	static const Table<KeywordType> keywords = 
	{
		{ "mut", KEYWORD_MUT },
		{ "function", KEYWORD_FUNC },
		{ "var", KEYWORD_VAR },
		{ "type", KEYWORD_TYPE },
		{ "return", KEYWORD_RETURN },
		{ "for", KEYWORD_FOR },
		{ "while", KEYWORD_WHILE },
		{ "loop", KEYWORD_LOOP },
		{ "continue", KEYWORD_CONTINUE },
		{ "break", KEYWORD_BREAK },
		{ "if", KEYWORD_IF },
		{ "then", KEYWORD_THEN },
		{ "else", KEYWORD_ELSE },
		{ "match", KEYWORD_MATCH },
		{ "case", KEYWORD_CASE },
		{ "struct", KEYWORD_STRUCT },
		{ "union", KEYWORD_UNION },
		{ "enum", KEYWORD_ENUM },
		{ "true", KEYWORD_TRUE },
		{ "false", KEYWORD_FALSE },
		{ "import", KEYWORD_IMPORT },
		{ "export", KEYWORD_EXPORT },
		{ "public", KEYWORD_PUBLIC },
		{ "private", KEYWORD_PRIVATE }
	};


	KeywordType get_keyword_type(const Token& token)
	{
		// TODO: optimize this (probably with new table)

		auto key = token.get_string();
		auto iter = keywords.find(key);

		return iter == keywords.end()
			? KEYWORD_NONE
			: iter->second;
	}
}
