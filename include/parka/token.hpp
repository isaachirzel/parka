#ifndef PARKA_TOKEN_HPP
#define PARKA_TOKEN_HPP

// local includes
#include "parka/util/file.hpp"
#include "parka/util/primitives.hpp"
#include "parka/util/string.hpp"

#define MAX_TOKEN_LENGTH 1024

enum class TokenType
{
	EndOfFile,
	Compound,
	Identifier,
	LeftParenthesis,
	RightParenthesis,
	LeftBracket,
	RightBracket,
	LeftBrace,
	RightBrace,
	Semicolon,
	Colon,
	Comma,
	Dot,
	Range,
	Elipsis,
	Ampersand,
	Pipe,
	Carrot,
	LeftBitShift,
	RightBitShift,
	BooleanNot,
	BooleanAnd,
	BooleanOr,
	BitwiseNot,
	BitwiseXor,
	Equals,
	NotEquals,
	LessThanOrEqualTo,
	GreaterThanOrEqualTo,
	LessThan,
	GreaterThan,
	SingleArrow,
	DoubleArrow,
	Option,
	Question,
	Assign,
	AddAssign,
	SubtractAssign,
	MultiplyAssign,
	DivideAssign,
	ModulusAssign,
	LeftBitShiftAssign,
	RightBitShiftAssign,
	BitwiseAndAssign,
	BitwiseOrAssign,
	BitwiseXorAssign,
	BooleanOrAssign,
	BooleanAndAssign,
	Modulus,
	Slash,
	Asterisk,
	Plus,
	Minus,
	Scope,
	IntegerLiteral,
	FloatLiteral,
	CharacterLiteral,
	StringLiteral,
	KeywordBreak,
	KeywordCase,
	KeywordContinue,
	KeywordYield,
	KeywordElse,
	KeywordEnum,
	KeywordExport,
	KeywordFalse,
	KeywordFor,
	KeywordFunction,
	KeywordIf,
	KeywordImport,
	KeywordLoop,
	KeywordMatch,
	KeywordMut,
	KeywordPrivate,
	KeywordPublic,
	KeywordReturn,
	KeywordStruct,
	KeywordThen,
	KeywordTrue,
	KeywordType,
	KeywordUnion,
	KeywordVar,
	KeywordWhile
};

class Token
{
	const File& _file;
	usize _pos;
	usize _length;
	TokenType _type;

public:

	Token(const File& file, usize pos, usize length, TokenType type) :
	_file(file),
	_pos(pos),
	_length(length),
	_type(type)
	{}
	Token(Token&&) = default;
	Token(const Token&) = default;
	~Token() = default;

	static Token initial(const File& file);

	void increment();

	bool operator ==(const Token& other) const;
	bool operator ==(const String& other) const;
	const auto& operator[](usize index) const { return _file[index]; }

	auto text() const { return _file.text().substr(_pos, _length); }
	String category() const;
	const auto *begin() const { return &_file[_pos]; }
	const auto *end() const { return &_file[_pos + _length]; }
	const auto& file() const { return _file; }
	const auto& pos() const { return _pos; }
	const auto& length() const { return _length; }
	const auto& type() const { return _type; }
};

#endif
