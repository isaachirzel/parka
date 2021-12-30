#ifndef WARBLER_AST_EXPRESSION_PREFIX_H
#define WARBLER_AST_EXPRESSION_PREFIX_H

// local headers
#include <warbler/token.h>
#include <warbler/error.h>

typedef enum PrefixType
{
	PREFIX_INCREMENT,
	PREFIX_DECREMENT,
	PREFIX_REFERENCE,
	PREFIX_DEREFERENCE
} PrefixType;

typedef struct Prefix
{
	PrefixType type;
} Prefix;

Error prefix_parse(Prefix *self, TokenIterator *iter);
void prefix_print(Prefix *self, unsigned depth);

#endif
