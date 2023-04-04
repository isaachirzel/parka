#ifndef PARKA_AST_KEYWORD_HPP
#define PARKA_AST_KEYWORD_HPP

#include "parka/token.hpp"
#include "parka/util/optional.hpp"

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
	Struct,
	Then,
	True,
	Type,
	Var,
	While
};

class Keyword
{
	Token _token;
	KeywordType _type;

	Keyword(const Token& token, KeywordType type) :
	_token(token),
	_type(type)
	{}

public:

	static KeywordType getKeywordType(const Token& token);
	static Optional<Keyword> parseBool(Token& token);
	static Optional<Keyword> parseStruct(Token& token);
	static Optional<Keyword> parseVar(Token& token);
	static Optional<Keyword> parseFunction(Token& token);
	static Optional<Keyword> parseOperator(Token& token);
	static Optional<Keyword> parseMut(Token& token);

	const auto& token() const { return _token; }
	const auto& type() const { return _type; }
};

#endif
