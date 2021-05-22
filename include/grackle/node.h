#ifndef NODE_H
#define NODE_H

// local includes
#include <grackle/token.h>

enum NodeType
{
	NODE_NO_TYPE,
	NODE_PROGRAM,
	NODE_STATEMENT,
};

typedef struct node
{
	char type;
	token_t *vals;
	unsigned valc;
	struct node *args;
	unsigned argc;
} node_t;

node_t *node_create(char type, 

#endif
