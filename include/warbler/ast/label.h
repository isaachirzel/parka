#ifndef WARBLER_AST_LABEL_H
#define WARBLER_AST_LABEL_H

#include <warbler/error.h>
#include <warbler/token.h>
#include <warbler/ast/identifier.h>

typedef struct Label
{
	Identifier identifier;
} Label;

void label_init(Label *label);
void label_free(Label *label);
Error label_parse(Label *label, TokenIterator *iter);

#endif
