#ifndef WARBLER_TOKENIZER_H
#define WARBLER_TOKENIZER_H

// local includes
#include <grackle/data/token.h>

#define MAX_KEYWORD_LENGTH (15)

extern void initTokenizer();
extern void destroyTokenizer();
extern Token *tokenize(const char *src);

#endif
