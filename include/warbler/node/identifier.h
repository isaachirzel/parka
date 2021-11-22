#ifndef WARBLER_IDENTIFIER_H
#define WARBLER_IDENTIFIER_H

#include <warbler/data/string.h>

typedef struct Identifier
{
	const String *str;
}
Identifier;

extern Identifier *parseIdentifier(const Token *token);

#endif
