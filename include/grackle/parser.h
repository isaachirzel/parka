#ifndef PARSER_H
#define PARSER_H

// local includes
#include <grackle/toklist.h>

typedef struct node
{
	int a;
	char type;
} node_t;

node_t parse(toklist_t *toks);

#endif
