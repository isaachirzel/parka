#include "parka/ir/Primitive.hpp"
#include "parka/log/Log.hpp"
#include "parka/symbol/Resolvable.hpp"
#include "parka/util/Array.hpp"

namespace parka::ir
{
	const Array<Primitive*> Primitive::primitives = initPrimitives();

	Primitive Primitive::voidPrimitive("void", PrimitiveType::Void, 0);
	Primitive Primitive::u8Primitive("u8", PrimitiveType::UnsignedInteger, 1);
	Primitive Primitive::u16Primitive("u16", PrimitiveType::UnsignedInteger, 2);
	Primitive Primitive::u32Primitive("u32", PrimitiveType::UnsignedInteger, 4);
	Primitive Primitive::u64Primitive("u64", PrimitiveType::UnsignedInteger, 8);
	Primitive Primitive::i8Primitive("i8", PrimitiveType::SignedInteger, 1);
	Primitive Primitive::i16Primitive("i16", PrimitiveType::SignedInteger, 2);
	Primitive Primitive::i32Primitive("i32", PrimitiveType::SignedInteger, 4);
	Primitive Primitive::i64Primitive("i64", PrimitiveType::SignedInteger, 8);
	Primitive Primitive::f32Primitive("f32", PrimitiveType::FloatingPoint, 4);
	Primitive Primitive::f64Primitive("f64", PrimitiveType::FloatingPoint, 8);
	Primitive Primitive::boolPrimitive("bool", PrimitiveType::Boolean, 1);
	Primitive Primitive::charPrimitive("char", PrimitiveType::Character, 1);
	Primitive Primitive::stringPrimitive("string", PrimitiveType::String, 0);

	Array<Primitive*> Primitive::initPrimitives()
	{
		Array<Primitive*> primitives(14);

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

	Primitive::Primitive(const char *name, PrimitiveType type, u32 size):
	Resolvable(ResolvableType::Primitive),
	Resolution(ResolvableType::Primitive),
	_name(name),
	_size(size),
	_type(type)
	{}

	const Type *Primitive::valueType() const
	{
		log::error("Unable to get value of primitive `$`.", _name);
		
		return nullptr;
	}
}
