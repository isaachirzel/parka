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
	out->val = NULL;
	out->args = NULL;
	out->argc = 0;

	return out;
}


void node_destroy(node_t *node)
{
	if (!node) return;
	// destroy all leaves
	if (node->argc > 0) 
	{
		for (unsigned i = 0; i < node->argc; ++i)
		{
			node_destroy(node->args[i]);
		}
		free(node->args);
	}
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


static void print_recurse(const node_t *node, unsigned depth)
{
	// value node
	if (node->val)
	{
		for (unsigned i = 0; i < depth - 1; ++i)
		{
			fputs("|   ", stdout);
		}
		fputs("  > ", stdout);
		string_put(&node->val->str);
	}
	for (unsigned i = 0; i < node->argc; ++i)
	{
		print_recurse(node->args[i], depth + 1);
	}
	// arg node
}


void node_print(const node_t *node)
{
	return print_recurse(node, 1);
}
