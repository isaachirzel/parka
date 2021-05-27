#ifndef LEX_H
#define LEX_H

// local includes
#include <grackle/container/toklist.h>
#include <grackle/data/string.h> 

#define MAX_KEYWORD_LENGTH 15

enum CHAR_TYPES
{
	CHAR_NO_TYPE,
	CHAR_INVALID,
	CHAR_IDENTIFIER,
	CHAR_SEPARATOR,
	CHAR_DOT,
	CHAR_DIGIT,
	CHAR_OPERATOR,
	CHAR_QUOTE
};

// Lexer functions
extern void lex_init();
extern void lex_cleanup();
extern toklist_t *lex(char *src);

#endif
