#ifndef WARBLER_TOKEN_H
#define WARBLER_TOKEN_H

// local includes
#include <warbler/data/string.h>

typedef enum TokenType
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
} TokenType;

typedef struct Token
{
	String string;
	size_t line;
	size_t col;
	TokenType type;
}
Token;

Token token_default();
Token token_create(String* string, size_t line, size_t col, TokenType type);

#endif
