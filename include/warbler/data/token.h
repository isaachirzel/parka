#ifndef GRACKLE_TOKEN_H
#define GRACKLE_TOKEN_H

// local includes
#include <warbler/data/string.h>

namespace warbler
{
	class Token
	{
	public: // types

		enum Type
		{	
			END_OF_FILE,
			IDENTIFIER,
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
			DOT,
			ELIPSIS,
			AMPERSAND,
			PIPELINE,
			CARROT,
			LSHIFT,
			RSHIFT,
			EXCLAMATION,
			AND,
			OR,
			EQUALS,
			NEQUALS,
			LTOET,
			GTOET,
			SINGLE_ARROW,
			DOUBLE_ARROW,
			ASSIGN,
			ADD_ASSIGN,
			SUB_ASSIGN,
			MUL_ASSIGN,
			DIV_ASSIGN,
			MOD_ASSIGN,
			LSHIFT_ASSIGN,
			RSHIFT_ASSIGN,
			MODULUS,
			SLASH,
			ASTERISK,
			PLUS,
			POW,
			MINUS,
			INCREMENT,
			DECREMENT,
			INT_LITERAL,
			FLOAT_LITERAL,
			HEX_LITERAL,
			BIN_LITERAL,
			OCT_LITERAL,
			CHAR_LITERAL,
			STR_LITERAL,
			TRUE,
			FALSE,
			VAR,
			FUNC,
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
			COUNT
		};

	private: // members

		String _str;
		size_t _line;
		size_t _col;
		Type _type;
	
	public: // methods

		Token();
		Token(String&& str, size_t line, size_t col, Type type);
		Token(Token&&) = default;
		Token(const Token&) = default;

		const String& str() const { return _str; }
		size_t line() const { return _line; }
		size_t col() const { return _col; }
		Type type() const { return _type; }
	};
}

#endif
