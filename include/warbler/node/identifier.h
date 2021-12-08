#ifndef WARBLER_NODE_IDENTIFIER_H
#define WARBLER_NODE_IDENTIFIER_H

// local includes
#include <warbler/error.h>
#include <warbler/data/string.h>
#include <warbler/data/token.h>

typedef struct Identifier
{
	String string;
} Identifier;

Error identifier_parse(Identifier **out, const Token **tokens);

#endif
