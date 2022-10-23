#include <warbler/context.h>
#include <warbler/util/print.h>
#include <warbler/symbol_table.h>

const PrimitiveContext primitives[] =
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
	{ "char", PRIMITIVE_CHARACTER, 1 }
};

const usize primitiveCount = sizeof(primitives) / sizeof(*primitives);

const PrimitiveContext *primitiveAt(usize index)
{
	assert(index < primitiveCount);

	return primitives + index;
}

const char *typeAnnotationSymbol(const TypeContext *type, const ProgramContext *program)
{
	switch (type->type)
	{
		case ANNOTATION_STRUCT:
		{
			const StructContext *context = structAt(program, type->index);

			return context->symbol;
		}

		case ANNOTATION_PRIMITIVE:
		{
			const PrimitiveContext *context = primitiveAt(type->index);

			return context->symbol;
		}

		case ANNOTATION_CONSTANT:
		default:
			exitWithError("Invalid TypeAnnotationType: %d", type->type);
	}
}
