#ifndef WARBLER_TOKENIZER_H
#define WARBLER_TOKENIZER_H

#define MAX_KEYWORD_LENGTH (15)
#define CHAR_TYPE_COUNT (128)

// local includes
#include <warbler/data/token.h>

// external libraries
#include <hirzel/array.h>

typedef enum CharType
{
	CHAR_INVALID,
	CHAR_IDENTIFIER,
	CHAR_SEPARATOR,
	CHAR_DOT,
	CHAR_DIGIT,
	CHAR_OPERATOR,
	CHAR_QUOTE
} CharType;

 ErrorType tokenizer_init();
 void tokenizer_free();

 HxArray *tokenize(const char *src);

#endif
