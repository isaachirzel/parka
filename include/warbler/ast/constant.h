#ifndef WARBLER_AST_CONSTANT_H
#define WARBLER_AST_CONSTANT_H

#include <warbler/error.h>
#include <warbler/token.h>

typedef enum ConstantType
{
	CONSTANT_INTEGER,
	CONSTANT_CHAR,
	CONSTANT_STRING,
	CONSTANT_FLOAT
} ConstantType;

typedef struct Constant
{
	ConstantType type;
	char *text;
} Constant;

void constant_init(Constant *constant);
void constant_free(Constant *constant);
Error constant_parse(Constant *out, TokenIterator *iter);

#endif
