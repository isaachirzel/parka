#ifndef WARBLER_LEXICON_TOKEN_HPP
#define WARBLER_LEXICON_TOKEN_HPP

// local includes
#include <warbler/source/file.hpp>

namespace warbler::source
{
	class Snippet;
}

namespace warbler::lexicon
{
	enum class TokenType
	{
		EndOfFile,
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
		Pipeline,
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
		HexadecimalLiteral,
		BinaryLiteral,
		OctalLiteral,
		CharLiteral,
		StringLiteral,
		KeywordBreak,
		KeywordCase,
		KeywordContinue,
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
		KeywordWhile,
	};

	class Token
	{
	private:

		const source::File& _file;
		usize _pos;
		usize _length;
		TokenType _type;

	public:

		Token(const source::File& file, usize pos, usize length, TokenType type);

		static Token get_initial(const source::File& file);

		Token& next();

		const source::File& file() const { return _file; }
		usize pos() const { return _pos; }
		usize length() const { return _length; }
		TokenType type() const { return _type; }
		String text() const { return _file.get_text(_pos, _length); }
		operator String() const;
		const char *category() const;
	};
}

#endif
