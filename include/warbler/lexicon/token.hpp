#ifndef WARBLER_TOKEN_HPP
#define WARBLER_TOKEN_HPP

// local includes
#include <warbler/util/array.hpp>
#include <warbler/util/table.hpp>
#include <warbler/source/snippet.hpp>
#include <warbler/source/location.hpp>

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
		Modulus,
		Slash,
		Asterisk,
		Plus,
		Minus,
		Pow,
		IntegerLiteral,
		FloatLiteral,
		HexadecimalLiteral,
		BinaryLiteral,
		OctalLiteral,
		CharLiteral,
		StringLiteral,
		Scope,

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

		source::Location _location;
		TokenType _type;

	public:

		Token(const source::Location& location, TokenType type);

		source::Snippet get_snippet() const { return _location.get_snippet(); }
		String get_string() const { return _location.text(); }

		bool is_keyword();

		const source::Location& location() const { return _location; }
		TokenType type() const { return _type; }
	};

	typedef Array<Token>::const_iterator TokenIterator;
}

#endif
