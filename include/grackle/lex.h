#ifndef LEX_H
#define LEX_H

// local includes
#include <grackle/toklist.h>
#include <grackle/defs.h> 

enum CHAR_TYPES
{
	CHAR_NO_TYPE,
	CHAR_INVALID,
	CHAR_IDENTIFIER,
	CHAR_SEPARATOR,
	CHAR_DIGIT,
	CHAR_OPERATOR,
	CHAR_LITERAL
};

// Lexer functions
void lex_init();
toklist_t *lex(const char *src);

#endif
