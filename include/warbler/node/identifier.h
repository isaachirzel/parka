#ifndef WARBLER_IDENTIFIER_H
#define WARBLER_IDENTIFIER_H

// local includes
#include <warbler/data/string.h>
#include <warbler/data/token.h>

typedef struct Identifier
{
	const String *str;
}
Identifier;

extern Identifier *parseIdentifier(const Token *token);

#endif
