#ifndef WARBLER_AST_PARAMETER_H
#define WARBLER_AST_PARAMETER_H

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

void parameter_init(Parameter *parameter);
void parameter_free(Parameter *parameter);
Error parameter_parse(Parameter *out, TokenIterator *iter);

void parameter_list_init(ParameterList *list);
void parameter_list_free(ParameterList *list);
Error parameter_list_parse(ParameterList *out, TokenIterator *iter);

#endif
