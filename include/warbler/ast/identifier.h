#ifndef WARBLER_AST_IDENTIFIER_H
#define WARBLER_AST_IDENTIFIER_H

#include <warbler/error.h>
#include <warbler/token.h>

typedef struct Identifier
{
	char *text;
} Identifier;

void identifier_init(Identifier *identifier);
void identifier_free(Identifier *identifier);
Error identifier_parse(Identifier *out, TokenIterator *iter);

#endif
