#ifndef PARKA_AST_KEYWORD_HPP
#define PARKA_AST_KEYWORD_HPP

#include "parka/enum/KeywordType.hpp"
#include "parka/util/Result.hpp"
#include "parka/parser/Token.hpp"
#include "parka/util/Table.hpp"

namespace parka::ast
{
	class KeywordAst
	{
		Snippet _snippet;
		KeywordType _type;

	public:

		static const Table<String, KeywordType> keywords;

	private:

		static Table<String, KeywordType> initKeywords();

	public:

		KeywordAst(const Snippet& snippet, KeywordType type):
		_snippet(snippet),
		_type(type)
		{}
		KeywordAst(KeywordAst&&) = default;
		KeywordAst(const KeywordAst&) = delete;

		static KeywordType getKeywordType(const String& text);
		static Result<KeywordAst> parseBoolKeyword(Token& token);
		static Result<KeywordAst> parseStructKeyword(Token& token);
		static Result<KeywordAst> parseVarKeyword(Token& token);
		static Result<KeywordAst> parseFunctionKeyword(Token& token);
		static Result<KeywordAst> parseOperatorKeyword(Token& token);
		static Result<KeywordAst> parseMutKeyword(Token& token);

		const Snippet& snippet() const { return _snippet; }
		const auto& type() const { return _type; }
	};
}

#endif
