#ifndef WARBLER_AST_CONSTANT_H
#define WARBLER_AST_CONSTANT_H

// local headers
#include <warbler/error.h>
#include <warbler/token.h>
#include <warbler/primitive.h>

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

void constant_init(Constant *constant);
void constant_free(Constant *constant);
Error constant_parse(Constant *out, TokenIterator *iter);

#endif
