#include "parka/intrinsic/Primitive.hpp"

namespace parka
{
	const Primitive Primitive::primitives[] =
	{
		{ "void", PrimitiveType::Void, 0 },
		{ "u8", PrimitiveType::UnsignedInteger, 1 },
		{ "u16", PrimitiveType::UnsignedInteger, 2 },
		{ "u32", PrimitiveType::UnsignedInteger, 4 },
		{ "u64", PrimitiveType::UnsignedInteger, 8 },
		{ "i8", PrimitiveType::SignedInteger, 1 },
		{ "i16", PrimitiveType::SignedInteger, 2 },
		{ "i32", PrimitiveType::SignedInteger, 4 },
		{ "i64", PrimitiveType::SignedInteger, 8 },
		{ "f32", PrimitiveType::FloatingPoint, 4 },
		{ "f64", PrimitiveType::FloatingPoint, 8 },
		{ "bool", PrimitiveType::Boolean, 1 },
		{ "char", PrimitiveType::Character, 1 },
		{ "string", PrimitiveType::String, 0 }
	};
	const usize Primitive::primitiveCount = sizeof(primitives) / sizeof(*primitives);
}
