#ifndef WARBLER_NODE_IDENTIFIER_H
#define WARBLER_NODE_IDENTIFIER_H

// local includes
#include <warbler/data/string.h>
#include <warbler/data/token.h>

typedef struct Identifier
{
	const String *str;
}
Identifier;

extern Identifier *identifier_parse(const Token *token);

#endif
