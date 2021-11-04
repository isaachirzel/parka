#ifndef GRACKLE_TOKEN_H
#define GRACKLE_TOKEN_H

#include <string_view>
#include <vector>

namespace grackle
{
	class Token
	{
	public:
		enum Type
		{
			// Generic
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

	private:

		std::string_view str;
		Type type;
		unsigned line;
		unsigned col;
	};

	using TokenList = std::vector<Token>;
	using TokenIter = std::vector<Token>::iterator;
}

#endif
