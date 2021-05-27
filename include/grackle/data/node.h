#ifndef NODE_H
#define NODE_H

// local includes
#include <grackle/data/token.h>
#include <stdbool.h>

enum NodeType
{
	NODE_NO_TYPE = TOK_COUNT,
	NODE_PROGRAM,
	NODE_FUNCTION,
	NODE_COMPOUND_STMT,
	NODE_VAR_DECLARATION,
	NODE_TYPE_DECLARATION,
	NODE_INITIALIZATION_STMT,
	NODE_EXPRESSION,
	NODE_IDENTIFIER,
	NODE_TYPENAME,
	NODE_ARGLIST,
	NODE_EMPTY_TYPE,

	// Last
	NODE_COUNT,
};

typedef struct node
{
	short type;
	token_t *val;
	struct node **args;
	unsigned argc;
} node_t;

extern node_t *node_create(char type);
extern void node_destroy(node_t *node);
extern bool node_push_arg(node_t *node, node_t *arg);
extern void node_print(node_t *node);

#endif
