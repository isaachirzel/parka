#ifndef TOKEN_H
#define TOKEN_H

#include <grackle/defs.h>

enum TokenType
{
	TOK_NO_TYPE,
	TOK_ERROR,
	TOK_IDENTIFIER,
	TOK_INT_TYPE,
	TOK_DOUBLE_TYPE,
	TOK_NUM_LITERAL,
	TOK_CHAR_LITERAL,
	TOK_STR_LITERAL,
	TOK_RETURN,
	TOK_ASSIGN,
	TOK_SEMICOLON,
	TOK_ADD_ASSIGN,
};

typedef struct token
{
	StringView str;
	char type;
} token_t;

extern token_t token_create();

#endif