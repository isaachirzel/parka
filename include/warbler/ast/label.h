#ifndef WARBLER_AST_LABEL_H
#define WARBLER_AST_LABEL_H

#include <warbler/error.h>
#include <warbler/token.h>
#include <warbler/ast/identifier.h>

typedef struct Label
{
	Identifier *identifier;
} Label;

Error label_parse(Label *out, TokenIterator *iter);
void label_free(Label *label);

#endif
