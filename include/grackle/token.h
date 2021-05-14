#ifndef TOKEN_H
#define TOKEN_H

#include <grackle/defs.h>

enum TokenType
{
	TOK_NO_TYPE,
	TOK_IDENTIFIER,
	TOK_ASSIGN
};

typedef struct token
{
	StringView str;
	char type;
} token_t;

extern token_t token_create();

#endif