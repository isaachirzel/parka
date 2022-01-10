#ifndef WARBLER_AST_CONSTANT_HPP
#define WARBLER_AST_CONSTANT_HPP

// local headers
#include <warbler/result.hpp>
#include <warbler/token.hpp>
#include <warbler/primitive.hpp>
namespace warbler
{
typedef enum ConstantType
{
	CONSTANT_CHAR,
	CONSTANT_STRING,
	CONSTANT_INTEGER,
	CONSTANT_FLOAT
} ConstantType;

typedef struct Constant
{
	union
	{
		i64 integer;
		f64 float64;
		u32 character;
		char *string;
	};
	ConstantType type;
} Constant;

void constant_init(Constant *self);
void constant_free(Constant *self);
Error constant_parse(Constant *self, TokenIterator& iter);
void constant_print_tree(Constant *self, unsigned depth);
}
#endif
