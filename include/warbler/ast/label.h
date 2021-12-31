#ifndef WARBLER_AST_LABEL_H
#define WARBLER_AST_LABEL_H

#include <warbler/error.h>
#include <warbler/token.h>
#include <warbler/ast/identifier.h>

typedef struct Label
{
	Identifier identifier;
} Label;

void label_init(Label *self);
void label_free(Label *self);
Error label_parse(Label *self, TokenIterator *iter);
void label_print_tree(Label *self, unsigned depth);

#endif
