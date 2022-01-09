#ifndef WARBLER_TOKENIZER_H
#define WARBLER_TOKENIZER_H

#define MAX_KEYWORD_LENGTH (15)
#define CHAR_TYPE_COUNT (128)
#define TEMP_KEY_SIZE (1023)

// local includes
#include <warbler/token.h>
#include <warbler/error.h>
#include <warbler/token_array.h>

Error tokenizer_init();
void tokenizer_free();

Error tokenize(TokenArray *out, const char *filename, const char *src);

#endif
