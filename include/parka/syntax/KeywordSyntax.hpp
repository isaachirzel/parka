#ifndef PARKA_SYNTAX_KEYWORD_SYNTAX_HPP
#define PARKA_SYNTAX_KEYWORD_SYNTAX_HPP

#include "parka/Token.hpp"
#include "parka/util/Optional.hpp"

namespace parka
{
	enum class KeywordType
	{
		None,
		Break,
		Case,
		Continue,
		Yield,
		Else,
		Enum,
		Export,
		False,
		For,
		Function,
		Operator,
		If,
		Import,
		Loop,
		Match,
		Mut,
		Private,
		Public,
		Return,
		StructSyntax,
		Then,
		True,
		Type,
		Var,
		While
	};

	class KeywordSyntax
	{
		Token _token;
		KeywordType _type;

		KeywordSyntax(const Token& token, KeywordType type) :
		_token(token),
		_type(type)
		{}

	public:

		static KeywordType getKeywordType(const Token& token);
		static Optional<KeywordSyntax> parseBool(Token& token);
		static Optional<KeywordSyntax> parseStruct(Token& token);
		static Optional<KeywordSyntax> parseVar(Token& token);
		static Optional<KeywordSyntax> parseFunction(Token& token);
		static Optional<KeywordSyntax> parseOperator(Token& token);
		static Optional<KeywordSyntax> parseMut(Token& token);

		const auto& token() const { return _token; }
		const auto& type() const { return _type; }
	};
}

#endif
