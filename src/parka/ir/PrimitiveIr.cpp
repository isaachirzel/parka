#include "parka/ir/PrimitiveIr.hpp"
#include "parka/ir/LValueIr.hpp"
#include "parka/validation/Resolvable.hpp"

namespace parka::ir
{
	PrimitiveIr PrimitiveIr::voidPrimitive = { "void", PrimitiveType::Void, 0 };
	PrimitiveIr PrimitiveIr::u8Primitive = { "u8", PrimitiveType::UnsignedInteger, 1 };
	PrimitiveIr PrimitiveIr::u16Primitive = { "u16", PrimitiveType::UnsignedInteger, 2 };
	PrimitiveIr PrimitiveIr::u32Primitive = { "u32", PrimitiveType::UnsignedInteger, 4 };
	PrimitiveIr PrimitiveIr::u64Primitive = { "u64", PrimitiveType::UnsignedInteger, 8 };
	PrimitiveIr PrimitiveIr::i8Primitive = { "i8", PrimitiveType::SignedInteger, 1 };
	PrimitiveIr PrimitiveIr::i16Primitive = { "i16", PrimitiveType::SignedInteger, 2 };
	PrimitiveIr PrimitiveIr::i32Primitive = { "i32", PrimitiveType::SignedInteger, 4 };
	PrimitiveIr PrimitiveIr::i64Primitive = { "i64", PrimitiveType::SignedInteger, 8 };
	PrimitiveIr PrimitiveIr::f32Primitive = { "f32", PrimitiveType::FloatingPoint, 4 };
	PrimitiveIr PrimitiveIr::f64Primitive = { "f64", PrimitiveType::FloatingPoint, 8 };
	PrimitiveIr PrimitiveIr::boolPrimitive = { "bool", PrimitiveType::Boolean, 1 };
	PrimitiveIr PrimitiveIr::charPrimitive = { "char", PrimitiveType::Character, 1 };
	PrimitiveIr PrimitiveIr::stringPrimitive = { "string", PrimitiveType::String, 8 };
	PrimitiveIr* PrimitiveIr::entries[] =
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
	const usize PrimitiveIr::entryCount = sizeof(entries) / sizeof(entries[0]);

	PrimitiveIr::PrimitiveIr(const char *name, PrimitiveType type, u32 size):
		Resolvable(ResolvableType::Primitive),
		LValueIr(ResolvableType::Primitive),
		_name(name),
		_size(size),
		_type(type)
	{
		assert(name != nullptr);
	}
}
