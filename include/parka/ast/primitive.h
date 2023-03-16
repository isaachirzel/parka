#ifndef PARKA_AST_PRIMITIVE_H
#define PARKA_AST_PRIMITIVE_H

#include "parka/ast/operator.h"
#include "parka/util/primitives.h"

enum PrimitiveIndex
{
	INDEX_VOID,
	INDEX_U8,
	INDEX_16,
	INDEX_U32,
	INDEX_U64,
	INDEX_I8,
	INDEX_I16,
	INDEX_I32,
	INDEX_I64,
	INDEX_F32,
	INDEX_F64,
	INDEX_BOOL,
	INDEX_CHAR,
	INDEX_STRING,
};

typedef enum PrimitiveType
{
	PRIMITIVE_VOID,
	PRIMITIVE_UNSIGNED_INTEGER,
	PRIMITIVE_SIGNED_INTEGER,
	PRIMITIVE_FLOATING_POINT,
	PRIMITIVE_BOOLEAN,
	PRIMITIVE_CHARACTER,
	PRIMITIVE_STRING
} PrimitiveType;

typedef struct Primitive
{
	const char * const symbol;
	PrimitiveType const type;
	u32 const size;
	Operators operators;
} Primitive;

extern Primitive primitives[];
extern const usize primitiveCount;

void primitiveInitAll();

#endif
