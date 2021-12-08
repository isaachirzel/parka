#ifndef WARBLER_TOKEN_H
#define WARBLER_TOKEN_H

// local includes
#include <warbler/data/string.h>

typedef enum TokenType
{
	TOKEN_END_OF_FILE,
	TOKEN_IDENTIFIER,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_LBRACK,
	TOKEN_RBRACK,
	TOKEN_LBRACE,
	TOKEN_RBRACE,
	TOKEN_LANGBRACK,
	TOKEN_RANGBRACK,
	TOKEN_SEMICOLON,
	TOKEN_COLON,
	TOKEN_COMMA,
	TOKEN_DOT,
	TOKEN_ELIPSIS,
	TOKEN_AMPERSAND,
	TOKEN_PIPELINE,
	TOKEN_CARROT,
	TOKEN_LSHIFT,
	TOKEN_RSHIFT,
	TOKEN_EXCLAMATION,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_EQUALS,
	TOKEN_NEQUALS,
	TOKEN_LTOET,
	TOKEN_GTOET,
	TOKEN_SINGLE_ARROW,
	TOKEN_DOUBLE_ARROW,
	TOKEN_ASSIGN,
	TOKEN_ADD_ASSIGN,
	TOKEN_SUB_ASSIGN,
	TOKEN_MUL_ASSIGN,
	TOKEN_DIV_ASSIGN,
	TOKEN_MOD_ASSIGN,
	TOKEN_LSHIFT_ASSIGN,
	TOKEN_RSHIFT_ASSIGN,
	TOKEN_MODULUS,
	TOKEN_SLASH,
	TOKEN_ASTERISK,
	TOKEN_PLUS,
	TOKEN_POW,
	TOKEN_MINUS,
	TOKEN_INCREMENT,
	TOKEN_DECREMENT,
	TOKEN_INTEGER,
	TOKEN_FLOAT,
	TOKEN_HEXADECIMAL,
	TOKEN_BINARY,
	TOKEN_OCTAL,
	TOKEN_CHAR,
	TOKEN_STRING,
	TOKEN_TRUE,
	TOKEN_FALSE,
	TOKEN_VAR,
	TOKEN_FUNC,
	TOKEN_RETURN,
	TOKEN_FOR,
	TOKEN_WHILE,
	TOKEN_LOOP,
	TOKEN_CONTINUE,
	TOKEN_BREAK,
	TOKEN_IF,
	TOKEN_ELSE,
	TOKEN_SWITCH,
	TOKEN_CASE,
	TOKEN_TYPE,
	TOKEN_STRUCT,
	TOKEN_ENUM,
	TOKEN_UNION,
	TOKEN_IMPORT,
	TOKEN_EXPORT,
	TOKEN_SCOPE,
	TOKEN_COUNT
} TokenType;

typedef struct Token
{
	String string;
	size_t line;
	size_t col;
	TokenType type;
} Token;

Token token_default();
Token token_create(String* string, size_t line, size_t col, TokenType type);

#endif
