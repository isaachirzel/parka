#include "parka/ir/Type.hpp"
#include "parka/ir/Primitive.hpp"

namespace parka::ir
{
	const Type Type::voidType(Primitive::voidPrimitive);
	const Type Type::u8Type(Primitive::u8Primitive);
	const Type Type::u16Type(Primitive::u16Primitive);
	const Type Type::u32Type(Primitive::u32Primitive);
	const Type Type::u64Type(Primitive::u64Primitive);
	const Type Type::i8Type(Primitive::i8Primitive);
	const Type Type::i16Type(Primitive::i16Primitive);
	const Type Type::i32Type(Primitive::i32Primitive);
	const Type Type::i64Type(Primitive::i64Primitive);
	const Type Type::f32Type(Primitive::f32Primitive);
	const Type Type::f64Type(Primitive::f64Primitive);
	const Type Type::boolType(Primitive::boolPrimitive);
	const Type Type::charType(Primitive::charPrimitive);
	const Type Type::stringType(Primitive::stringPrimitive);

	bool operator==(const Type& left, const Type& right)
	{
		return &left._typeBase == &right._typeBase;
	}

	bool operator!=(const Type& left, const Type& right)
	{
		return &left._typeBase != &right._typeBase;
	}
	
	std::ostream& operator<<(std::ostream& out, const Type& type)
	{
		out << "`" << type._typeBase << '`';

		return out;
	}
}
