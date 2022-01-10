#ifndef WARBLER_AST_PARAMETER_HPP
#define WARBLER_AST_PARAMETER_HPP

// local headers
#include <warbler/result.hpp>
#include <warbler/token.hpp>
#include <warbler/ast/typename.hpp>
#include <warbler/ast/identifier.hpp>
namespace warbler
{
typedef struct Parameter
{
	Identifier name;
	Typename type;
} Parameter;

typedef struct ParameterList
{
	Parameter *data;
	size_t count;
} ParameterList;

void parameter_init(Parameter *self);
void parameter_free(Parameter *self);
Error parameter_parse(Parameter *self, TokenIterator& iter);
void parameter_print_tree(Parameter *self, unsigned depth);

void parameter_list_init(ParameterList *self);
void parameter_list_free(ParameterList *self);
Error parameter_list_parse(ParameterList *self, TokenIterator& iter);
void parameter_list_print_tree(ParameterList *self, unsigned depth);
}
#endif
