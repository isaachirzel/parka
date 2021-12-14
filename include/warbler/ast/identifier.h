#ifndef WARBLER_AST_IDENTIFIER_H
#define WARBLER_AST_IDENTIFIER_H

#include <warbler/error.h>
#include <warbler/token.h>

typedef struct Identifier
{
	char *text;
} Identifier;

Error identifier_parse(Identifier *out, TokenIterator *iter);
void identifier_free(Identifier *identifier);

#endif
