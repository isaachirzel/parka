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
	NODE_TYPE_DECLARATION,
	// statements
	NODE_COMPOUND_STMT,
	NODE_DECL_STMT,

	// expressions
	NODE_ASSIGN_EXPR,
	NODE_OR_EXPR,
	NODE_AND_EXPR,
	NODE_BITOR_EXPR,
	NODE_BITXOR_EXPR,
	NODE_BITAND_EXPR,
	NODE_EQ_EXPR,
	NODE_COMP_EXPR,
	NODE_SHIFT_EXPR,
	NODE_ADD_EXPR,
	NODE_MUL_EXPR,
	NODE_TERM,
	NODE_UNARY_EXPR,

	// 
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
	const token_t *val;
	struct node **args;
	unsigned argc;
} node_t;

extern node_t *node_create(char type);
extern void node_destroy(node_t *node);
extern bool node_push_arg(node_t *node, node_t *arg);
extern void node_swap_parent(node_t **node, unsigned argi);
extern void node_print(const node_t *node);

#endif
