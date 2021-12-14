#ifndef WARBLER_AST_PARAMETER_H
#define WARBLER_AST_PARAMETER_H

#include <warbler/error.h>
#include <warbler/token.h>
#include <warbler/ast/typename.h>
#include <warbler/ast/identifier.h>

typedef struct Parameter
{
	Typename *typename;
	Identifier *identifier;
} Parameter;

typedef struct ParameterList
{
	Parameter *parameters;
	size_t count;
} ParameterList;

Error parameter_parse(Parameter *out, TokenIterator *iter);
void parameter_free(Parameter *parameter);

Error parameter_list_parse(ParameterList *out, TokenIterator *iter);
void parameter_list_free(ParameterList* list);
#endif
