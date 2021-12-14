#ifndef WARBLER_AST_TYPENAME_H
#define WARBLER_AST_TYPENAME_H

#include <warbler/error.h>
#include <warbler/token.h>

typedef struct Typename
{
	char *text;
} Typename;

void typename_init(Typename *typename);
void typename_free(Typename *typename);
Error typename_parse(Typename *out, TokenIterator *iter);

#endif
