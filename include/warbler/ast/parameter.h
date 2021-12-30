#ifndef WARBLER_AST_PARAMETER_H
#define WARBLER_AST_PARAMETER_H

// local headers
#include <warbler/error.h>
#include <warbler/token.h>
#include <warbler/ast/typename.h>
#include <warbler/ast/identifier.h>

typedef struct Parameter
{
	Identifier name;
	Typename type;
} Parameter;

typedef struct ParameterList
{
	Parameter *parameters;
	size_t parameter_count;
} ParameterList;

void parameter_init(Parameter *self);
void parameter_free(Parameter *self);
Error parameter_parse(Parameter *self, TokenIterator *iter);
void parameter_print_tree(Parameter *self, unsigned depth);

void parameter_list_init(ParameterList *self);
void parameter_list_free(ParameterList *self);
Error parameter_list_parse(ParameterList *self, TokenIterator *iter);
void parameter_list_print_tree(ParameterList *self, unsigned depth);

#endif
