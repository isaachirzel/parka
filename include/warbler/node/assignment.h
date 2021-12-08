#ifndef WARBLER_NODE_ASSIGNMENT_H
#define WARBLER_NODE_ASSIGNMENT_H

// local includes
#include <warbler/data/token.h>
#include <warbler/node/identifier.h>
#include <warbler/node/expression.h>

typedef struct Assignment
{
	Identifier left;
	Expression right;
} Assignment;

extern Error assignment_parse(Assignment **out, const Token *token);

#endif
