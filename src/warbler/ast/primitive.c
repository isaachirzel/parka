#include "warbler/ast/primitive.h"
#include "warbler/ast/operator.h"
#include "warbler/ast/type.h"
#include "warbler/symbol.h"
#include "warbler/util/array.h"

Primitive primitives[] =
{
	{ "void", PRIMITIVE_VOID, 0 },
	{ "u8", PRIMITIVE_UNSIGNED_INTEGER, 1 },
	{ "u16", PRIMITIVE_UNSIGNED_INTEGER, 2 },
	{ "u32", PRIMITIVE_UNSIGNED_INTEGER, 4 },
	{ "u64", PRIMITIVE_UNSIGNED_INTEGER, 8 },
	{ "i8", PRIMITIVE_SIGNED_INTEGER, 1 },
	{ "i16", PRIMITIVE_SIGNED_INTEGER, 2 },
	{ "i32", PRIMITIVE_SIGNED_INTEGER, 4 },
	{ "i64", PRIMITIVE_SIGNED_INTEGER, 8 },
	{ "f32", PRIMITIVE_FLOATING_POINT, 4 },
	{ "f64", PRIMITIVE_FLOATING_POINT, 8 },
	{ "bool", PRIMITIVE_BOOLEAN, 1 },
	{ "char", PRIMITIVE_CHARACTER, 1 },
	{ "string", PRIMITIVE_STRING, 0 }
};

const usize primitiveCount = sizeof(primitives) / sizeof(*primitives);

void primitiveInitAll()
{
	Primitive *i32 = &primitives[INDEX_I32];

	i32->operators = operatorsCreate();

	Operator operator = 
	{
		.type = OPERATOR_PLUS,
		.rightType = typeDuplicate(&i32Type),
		.returnType = typeDuplicate(&i32Type),
		.isBinary = true,
		.isConst = true,
	};

	arrayPush(&i32->operators.adds, &operator);
}
