#ifndef WARBLER_AST_TYPENAME_H
#define WARBLER_AST_TYPENAME_H

#include <warbler/error.h>
#include <warbler/token.h>

typedef struct Typename
{
	char *text;
} Typename;

Error typename_parse(Typename *out, TokenIterator *iter);

#endif
