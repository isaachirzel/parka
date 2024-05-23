#ifndef PARKA_ENUM_TOKEN_TYPE_HPP
#define PARKA_ENUM_TOKEN_TYPE_HPP

#include "parka/util/Common.hpp"

namespace parka
{
	enum class TokenType: u8
	{
		EndOfFile,
		Invalid,
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
		StringLiteral
	};
}

#endif
