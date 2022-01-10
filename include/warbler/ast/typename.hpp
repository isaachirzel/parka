#ifndef WARBLER_AST_TYPENAME_HPP
#define WARBLER_AST_TYPENAME_HPP

#include <warbler/result.hpp>
#include <warbler/token.hpp>
namespace warbler
{
struct Typename
{
	char *text;
};

void typename_init(Typename *self);
void typename_free(Typename *self);
Error typename_parse(Typename *self, TokenIterator& iter);
}
#endif
