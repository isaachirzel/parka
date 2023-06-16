#ifndef PARKA_SYNTAX_KEYWORD_SYNTAX_HPP
#define PARKA_SYNTAX_KEYWORD_SYNTAX_HPP

#include "parka/enum/KeywordType.hpp"
#include "parka/util/Optional.hpp"
#include "parka/Token.hpp"
#include "parka/util/Table.hpp"

namespace parka
{
	class KeywordSyntax
	{
		Snippet _snippet;
		KeywordType _type;

	public:

		static const Table<String, KeywordType> keywords;

	private:

		static Table<String, KeywordType> initKeywords();

	public:

		KeywordSyntax(const Snippet& snippet, KeywordType type) :
		_snippet(snippet),
		_type(type)
		{}
		KeywordSyntax(KeywordSyntax&&) = default;
		KeywordSyntax(const KeywordSyntax&) = delete;

		static KeywordType getKeywordType(const Token& token);
		static Optional<KeywordSyntax> parseBool(Token& token);
		static Optional<KeywordSyntax> parseStruct(Token& token);
		static Optional<KeywordSyntax> parseVar(Token& token);
		static Optional<KeywordSyntax> parseFunction(Token& token);
		static Optional<KeywordSyntax> parseOperator(Token& token);
		static Optional<KeywordSyntax> parseMut(Token& token);

		const Snippet& snippet() const { return _snippet; }
		const auto& type() const { return _type; }
	};
}

#endif
