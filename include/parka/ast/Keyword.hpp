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
		static Result<KeywordAst> parseBool(Token& token);
		static Result<KeywordAst> parseStruct(Token& token);
		static Result<KeywordAst> parseVar(Token& token);
		static Result<KeywordAst> parseFunction(Token& token);
		static Result<KeywordAst> parseOperator(Token& token);
		static Result<KeywordAst> parseMut(Token& token);

		const Snippet& snippet() const { return _snippet; }
		const auto& type() const { return _type; }
	};
}

#endif
