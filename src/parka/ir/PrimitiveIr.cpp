#include "parka/ir/PrimitiveIr.hpp"
#include "parka/ir/LValueIr.hpp"
#include "parka/symbol/Resolvable.hpp"

namespace parka::ir
{
	Primitive Primitive::voidPrimitive = { "void", PrimitiveType::Void, 0 };
	Primitive Primitive::u8Primitive = { "u8", PrimitiveType::UnsignedInteger, 1 };
	Primitive Primitive::u16Primitive = { "u16", PrimitiveType::UnsignedInteger, 2 };
	Primitive Primitive::u32Primitive = { "u32", PrimitiveType::UnsignedInteger, 4 };
	Primitive Primitive::u64Primitive = { "u64", PrimitiveType::UnsignedInteger, 8 };
	Primitive Primitive::i8Primitive = { "i8", PrimitiveType::SignedInteger, 1 };
	Primitive Primitive::i16Primitive = { "i16", PrimitiveType::SignedInteger, 2 };
	Primitive Primitive::i32Primitive = { "i32", PrimitiveType::SignedInteger, 4 };
	Primitive Primitive::i64Primitive = { "i64", PrimitiveType::SignedInteger, 8 };
	Primitive Primitive::f32Primitive = { "f32", PrimitiveType::FloatingPoint, 4 };
	Primitive Primitive::f64Primitive = { "f64", PrimitiveType::FloatingPoint, 8 };
	Primitive Primitive::boolPrimitive = { "bool", PrimitiveType::Boolean, 1 };
	Primitive Primitive::charPrimitive = { "char", PrimitiveType::Character, 1 };
	Primitive Primitive::stringPrimitive = { "string", PrimitiveType::String, 0 };
	Primitive* Primitive::entries[] =
	{
		&voidPrimitive,
		&u8Primitive,
		&u16Primitive,
		&u32Primitive,
		&u64Primitive,
		&i8Primitive,
		&i16Primitive,
		&i32Primitive,
		&i64Primitive,
		&f32Primitive,
		&f64Primitive,
		&boolPrimitive,
		&charPrimitive,
		&stringPrimitive
	};
	const usize Primitive::entryCount = sizeof(entries) / sizeof(entries[0]);

	Primitive::Primitive(const char *name, PrimitiveType type, u32 size):
		Resolvable(ResolvableType::Primitive),
		LValueIr(ResolvableType::Primitive),
		_name(name),
		_size(size),
		_type(type)
	{
		assert(name != nullptr);
	}
}
