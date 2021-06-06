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
	NODE_NOOP_STMT,
	NODE_DECL_STMT,
	NODE_RETURN_STMT,
	NODE_BREAK_STMT,
	NODE_CONTINUE_STMT,
	NODE_IF_STMT,
	NODE_WHILE_STMT,
	NODE_LOOP_STMT,
	NODE_SWITCH_STMT,

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
	NODE_SUFFIX_EXPR,
	NODE_PREFIX_EXPR,
	NODE_FACTOR,

	// suffixes
	NODE_INCREMENT,
	NODE_DECREMENT,
	NODE_FUNCTION_CALL,
	NODE_INDEX,

	// 
	NODE_IDENTIFIER,
	NODE_PARAMETER,
	NODE_TYPENAME,
	NODE_PARAM_LIST,
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
