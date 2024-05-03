#include "parka/ir/Primitive.hpp"
#include "parka/log/Log.hpp"
#include "parka/symbol/Resolvable.hpp"
#include "parka/util/Array.hpp"

namespace parka::ir
{
	Primitive Primitive::entries[] =
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
	const usize Primitive::entryCount = sizeof(entries) / sizeof(*entries);
	Primitive& Primitive::voidPrimitive = entries[0];
	Primitive& Primitive::u8Primitive = entries[1];
	Primitive& Primitive::u16Primitive = entries[2];
	Primitive& Primitive::u32Primitive = entries[3];
	Primitive& Primitive::u64Primitive = entries[4];
	Primitive& Primitive::i8Primitive = entries[5];
	Primitive& Primitive::i16Primitive = entries[6];
	Primitive& Primitive::i32Primitive = entries[7];
	Primitive& Primitive::i64Primitive = entries[8];
	Primitive& Primitive::f32Primitive = entries[9];
	Primitive& Primitive::f64Primitive = entries[10];
	Primitive& Primitive::boolPrimitive = entries[11];
	Primitive& Primitive::charPrimitive = entries[12];
	Primitive& Primitive::stringPrimitive = entries[13];

	Primitive::Primitive(const char *name, PrimitiveType type, u32 size):
		Resolvable(ResolvableType::Primitive),
		Resolution(ResolvableType::Primitive),
		_name(name),
		_size(size),
		_type(type)
	{
		assert(name != nullptr);
	}
}
