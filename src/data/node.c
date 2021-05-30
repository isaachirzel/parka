// header
#include <grackle/data/node.h>

// standard library
#include <stdlib.h>
#include <stdio.h>

node_t *node_create(char type)
{
	node_t *out = malloc(sizeof(node_t));
	if (!out) return NULL;

	out->type = type;
	out->args = NULL;
	out->val = NULL;
	out->argc = 0;

	return out;
}


void node_destroy(node_t *node)
{
	if (!node) return;
	// destroy all leaves
	for (unsigned i = 0; i < node->argc; ++i)
	{
		node_destroy(node->args[i]);
	}
	free(node->args);
	// free object
	free(node);
}


bool node_push_arg(node_t *node, node_t *arg)
{
	node_t **tmp = realloc(node->args, (node->argc + 1) * sizeof(node_t*));
	if (!tmp) return false;
	// repointing data and incrementing
	node->args = tmp;
	// pushing data onto list
	node->args[node->argc++] = arg;
	return true;
}


void node_swap_parent(node_t **node, unsigned argi)
{
	node_t *parent = *node;
	node_t *arg = parent->args[argi];
	
}


void node_print(node_t *node)
{
	if (node->val)
	{
		string_put(&node->val->str);
		return;
	}
	
	for (unsigned i = 0; i < node->argc; ++i)
	{
		node_print(node->args[i]);
	}
}
