#include "parka/intrinsic/Primitive.hpp"
#include "parka/util/Array.hpp"

namespace parka
{
	const Array<Primitive> Primitive::primitives = initPrimitives();

	Array<Primitive> Primitive::initPrimitives()
	{
		Array<Primitive> primitives(14);

		primitives.push(Primitive("void", PrimitiveType::Void, 0));
		primitives.push(Primitive("u8", PrimitiveType::UnsignedInteger, 1));
		primitives.push(Primitive("u16", PrimitiveType::UnsignedInteger, 2));
		primitives.push(Primitive("u32", PrimitiveType::UnsignedInteger, 4));
		primitives.push(Primitive("u64", PrimitiveType::UnsignedInteger, 8));
		primitives.push(Primitive("i8", PrimitiveType::SignedInteger, 1));
		primitives.push(Primitive("i16", PrimitiveType::SignedInteger, 2));
		primitives.push(Primitive("i32", PrimitiveType::SignedInteger, 4));
		primitives.push(Primitive("i64", PrimitiveType::SignedInteger, 8));
		primitives.push(Primitive("f32", PrimitiveType::FloatingPoint, 4));
		primitives.push(Primitive("f64", PrimitiveType::FloatingPoint, 8));
		primitives.push(Primitive("bool", PrimitiveType::Boolean, 1));
		primitives.push(Primitive("char", PrimitiveType::Character, 1));
		primitives.push(Primitive("string", PrimitiveType::String, 0));

		return primitives;
	}
}
