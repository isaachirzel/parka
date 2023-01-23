#ifndef WARBLER_AST_LITERAL_H
#define WARBLER_AST_LITERAL_H

#include "warbler/ast/type.h"
#include "warbler/token.h"
#include "warbler/util/primitives.h"

typedef enum LiteralType
{
	LITERAL_INTEGER,
	LITERAL_CHARACTER,
	LITERAL_STRING,
	LITERAL_FLOAT,
	LITERAL_BOOLEAN
	// TODO: add LITERAL_OBJECT
} LiteralType;

typedef struct StringLiteral
{
	char *text;
	usize length;
} StringLiteral;

typedef struct IntegerLiteral
{
	u64 integer;
	usize minBits;
} IntegerLiteral;

typedef struct Literal
{
	Token token;

	union
	{
		char character;
		StringLiteral string;
		IntegerLiteral integer;
		double floating;
		bool boolean;
	};

	LiteralType type;
} Literal;

void literalFree(Literal *node);
const char *literalTypeName(LiteralType type);
Type literalGetType(Literal *literal, const Type *expectedType);

#endif
