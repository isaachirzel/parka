#ifndef WARBLER_AST_EXPRESSION_PREFIX_HPP
#define WARBLER_AST_EXPRESSION_PREFIX_HPP

// local headers
#include <warbler/token.hpp>
#include <warbler/result.hpp>
namespace warbler
{
typedef enum PrefixType
{
	PREFIX_INCREMENT,
	PREFIX_DECREMENT,
	PREFIX_REFERENCE,
	PREFIX_DEREFERENCE
} PrefixType;

typedef struct Prefix
{
	PrefixType type;
} Prefix;

typedef struct PrefixList
{
	Prefix *data;
	size_t count;
} PrefixList;

Error prefix_parse(Prefix *self, TokenIterator& iter);
void prefix_print_tree(Prefix *self, unsigned depth);

void prefix_list_init(PrefixList *self);
void prefix_list_free(PrefixList *self);
Error prefix_list_parse(PrefixList *self, TokenIterator& iter);
void prefix_list_print_tree(PrefixList *self, unsigned depth);
}
#endif
