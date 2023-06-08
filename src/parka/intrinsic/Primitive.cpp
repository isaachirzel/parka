#include "parka/intrinsic/Primitive.hpp"
#include "parka/util/Array.hpp"

namespace parka
{
	const Array<const Primitive*> Primitive::primitives = initPrimitives();

	const Primitive Primitive::voidPrimitive("void", PrimitiveType::Void, 0);
	const Primitive Primitive::u8Primitive("u8", PrimitiveType::UnsignedInteger, 1);
	const Primitive Primitive::u16Primitive("u16", PrimitiveType::UnsignedInteger, 2);
	const Primitive Primitive::u32Primitive("u32", PrimitiveType::UnsignedInteger, 4);
	const Primitive Primitive::u64Primitive("u64", PrimitiveType::UnsignedInteger, 8);
	const Primitive Primitive::i8Primitive("i8", PrimitiveType::SignedInteger, 1);
	const Primitive Primitive::i16Primitive("i16", PrimitiveType::SignedInteger, 2);
	const Primitive Primitive::i32Primitive("i32", PrimitiveType::SignedInteger, 4);
	const Primitive Primitive::i64Primitive("i64", PrimitiveType::SignedInteger, 8);
	const Primitive Primitive::f32Primitive("f32", PrimitiveType::FloatingPoint, 4);
	const Primitive Primitive::f64Primitive("f64", PrimitiveType::FloatingPoint, 8);
	const Primitive Primitive::boolPrimitive("bool", PrimitiveType::Boolean, 1);
	const Primitive Primitive::charPrimitive("char", PrimitiveType::Character, 1);
	const Primitive Primitive::stringPrimitive("string", PrimitiveType::String, 0);

	Array<const Primitive*> Primitive::initPrimitives()
	{
		Array<const Primitive*> primitives(14);

		primitives.push(&voidPrimitive);
		primitives.push(&u8Primitive);
		primitives.push(&u16Primitive);
		primitives.push(&u32Primitive);
		primitives.push(&u64Primitive);
		primitives.push(&i8Primitive);
		primitives.push(&i16Primitive);
		primitives.push(&i32Primitive);
		primitives.push(&i64Primitive);
		primitives.push(&f32Primitive);
		primitives.push(&f64Primitive);
		primitives.push(&boolPrimitive);
		primitives.push(&charPrimitive);
		primitives.push(&stringPrimitive);

		return primitives;
	}
}
