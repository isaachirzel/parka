#ifndef PARSER_H
#define PARSER_H

// local includes
#include <grackle/toklist.h>

typedef struct node
{
	char type;
	token_t *val;
	struct node *children;
} node_t;

extern node_t parse(toklist_t *toks);

#endif
