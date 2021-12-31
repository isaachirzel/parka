#ifndef WARBLER_AST_ARGUMENT_H
#define WARBLER_AST_ARGUMENT_H

#include <warbler/error.h>
#include <warbler/token.h>

struct Expression;

typedef struct Argument
{
	struct Expression expr;
} Argument;

typedef struct ArgumentList
{
	Argument *arguments;
	size_t argument_count;
} ArgumentList;

void argument_init(Argument *self);
void argument_free(Argument *self);
Error argument_parse(Argument *self, TokenIterator *iter);
void argument_print_tree(Argument *self, unsigned depth);

void argument_list_init(ArgumentList *self);
void argument_list_free(ArgumentList *self);
Error argument_list_parse(ArgumentList *self, TokenIterator *iter);
void argument_list_print_tree(ArgumentList *self, unsigned depth);

#endif
