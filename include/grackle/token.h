#ifndef TOKEN_H
#define TOKEN_H

#include <grackle/string.h>

enum TokenType
{
	// Generic
	TOK_EOF,
	TOK_ERROR,
	TOK_IDENTIFIER,

	// Separators
	TOK_LPAREN,
	TOK_RPAREN,
	TOK_LBRACK,
	TOK_RBRACK,
	TOK_LBRACE,
	TOK_RBRACE,
	TOK_LANGBRACK,
	TOK_RANGBRACK,
	TOK_SEMICOLON,
	TOK_COLON,

	// Dot based
	TOK_DOT,		// 1 dot
	TOK_RANGE,		// 2 dots
	TOK_ELIPSIS,	// 3 dots

	// Bitwise
	TOK_AND_BIT,
	TOK_OR_BIT,
	TOK_XOR_BIT,

	// Boolean
	TOK_EXCLAMATION,
	TOK_AND_COMP,
	TOK_EQ_COMP,
	TOK_OR_COMP,
	TOK_NEQ_COMP,

	// Assignment
	TOK_ASSIGN,
	TOK_ADD_ASSIGN,
	TOK_MIN_ASSIGN,
	TOK_MUL_ASSIGN,
	TOK_DIV_ASSIGN,
	TOK_MOD_ASSIGN,

	// Arithmetic
	TOK_MODULUS,
	TOK_SLASH,
	TOK_ASTERISK,
	TOK_PLUS,
	TOK_MINUS,
	TOK_INCREMENT,
	TOK_DECREMENT,

	// Literals
	TOK_INT_LITERAL,
	TOK_FLOAT_LITERAL,
	TOK_HEX_LITERAL,	// todo
	TOK_BIN_LITERAL,	// todo
	TOK_OCT_LITERAL,	// todo
	TOK_CHAR_LITERAL,
	TOK_STR_LITERAL,

	// Typenames
	TOK_VAR,
	TOK_TYPENAME,
	TOK_I32_TYPE,

	// Keywords
	TOK_RETURN,
	TOK_FOR
};

typedef struct token
{
	string_t str;
	char type;
	unsigned line;
	unsigned short col;
} token_t;

extern token_t token_create();

#endif