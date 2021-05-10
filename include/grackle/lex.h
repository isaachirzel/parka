#ifndef LEX_H
#define LEX_H

#include <defs.h> 
#include <stddef.h>

typedef struct Token
{
	StringView str;
	char type;
} Token;

typedef struct TokenList
{
	Token *toks;
	size_t len;
} TokenList;

enum token_type {
	ERROR,
	ASSIGN
};

// Lexer functions
void lex_init();
TokenList *lex(const char *src);

// Token functions
Token token_create(const char *str, unsigned short len, char type);

// Token list functions
TokenList *token_list_create();
void token_list_push(TokenList* list, Token tok);




#endif
