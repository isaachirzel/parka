#ifndef TOKEN_H
#define TOKEN_H

#include <string_view>

class Token
{
public:
	enum Type
	{
		// Generic
		END_OF_FILE,
		ERROR,
		IDENTIFIER,

		// Separators
		LPAREN,
		RPAREN,
		LBRACK,
		RBRACK,
		LBRACE,
		RBRACE,
		LANGBRACK,
		RANGBRACK,
		SEMICOLON,
		COLON,
		COMMA,

		// Dot based
		DOT,		// 1 dot
		RANGE,		// 2 dots
		ELIPSIS,	// 3 dots

		// Bitwise
		AMPERSAND,
		PIPELINE,
		CARROT,
		LSHIFT,
		RSHIFT,

		// Boolean
		EXCLAMATION,
		AND,
		OR,
		EQUALS,
		NEQUALS,
		LTOET,
		GTOET,

		// Operators	===========================

		// Arrows
		SINGLE_ARROW,
		DOUBLE_ARROW,

		// Assignment
		ASSIGN,
		ADD_ASSIGN,
		SUB_ASSIGN,
		MUL_ASSIGN,
		DIV_ASSIGN,
		MOD_ASSIGN,
		LSHIFT_ASSIGN,
		RSHIFT_ASSIGN,

		// Arithmetic
		MODULUS,
		SLASH,
		ASTERISK,
		PLUS,
		POW,
		MINUS,
		INCREMENT,
		DECREMENT,

		// Literals
		INT_LITERAL,
		FLOAT_LITERAL,
		HEX_LITERAL,	// todo
		BIN_LITERAL,	// todo
		OCT_LITERAL,	// todo
		CHAR_LITERAL,
		STR_LITERAL,
		TRUE,
		FALSE,

		// Typenames
		VAR,
		FUNC,

		// Integer types
		TYPE_I8,
		TYPE_I16,
		TYPE_I32,
		TYPE_I64,
		TYPE_U8,
		TYPE_U16,
		TYPE_U32,
		TYPE_U64,
		TYPE_F32,
		TYPE_F64,
		TYPE_STR,
		TYPE_BOOL,

		// Keywords
		RETURN,
		FOR,
		WHILE,
		LOOP,
		CONTINUE,
		BREAK,
		IF,
		ELSE,
		SWITCH,
		CASE,
		TYPE,
		STRUCT,
		ENUM,
		UNION,
		IMPORT,
		EXPORT,
		SCOPE,

		// last
		COUNT
	};

private:
	std::string_view str;
	Type type;
	unsigned line;
	unsigned col;
};

#endif