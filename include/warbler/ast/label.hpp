#ifndef WARBLER_AST_LABEL_HPP
#define WARBLER_AST_LABEL_HPP

#include <warbler/result.hpp>
#include <warbler/token.hpp>
#include <warbler/ast/identifier.hpp>
namespace warbler
{
typedef struct Label
{
	Identifier identifier;
} Label;

void label_init(Label *self);
void label_free(Label *self);
Error label_parse(Label *self, TokenIterator& iter);
void label_print_tree(Label *self, unsigned depth);
}
#endif
