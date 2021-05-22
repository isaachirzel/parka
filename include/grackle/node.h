#ifndef NODE_H
#define NODE_H

// local includes
#include <grackle/token.h>
#include <stdbool.h>

enum NodeType
{
	NODE_NO_TYPE,
	NODE_PROGRAM,
	NODE_FUNCTION,
	NODE_COMPOUND_STMT,
	NODE_DELCARATION,
	NODE_INITIALIZATION_STMT,
	NODE_EXPRESSION,
	NODE_TYPENAME,
	NODE_IDENTIFIER,
	NODE_ARGLIST,
};

typedef struct node
{
	char type;
	token_t *val;
	struct node **args;
	unsigned argc;
} node_t;

extern node_t *node_create(char type);
extern void node_destroy(node_t *node);
extern bool node_push_arg(node_t *node, node_t *arg);

#endif
