#include "parka/ir/ValueType.hpp"
#include "parka/ir/Primitive.hpp"

namespace parka::ir
{
	const ValueType ValueType::voidType(Primitive::voidPrimitive);
	const ValueType ValueType::u8Type(Primitive::u8Primitive);
	const ValueType ValueType::u16Type(Primitive::u16Primitive);
	const ValueType ValueType::u32Type(Primitive::u32Primitive);
	const ValueType ValueType::u64Type(Primitive::u64Primitive);
	const ValueType ValueType::i8Type(Primitive::i8Primitive);
	const ValueType ValueType::i16Type(Primitive::i16Primitive);
	const ValueType ValueType::i32Type(Primitive::i32Primitive);
	const ValueType ValueType::i64Type(Primitive::i64Primitive);
	const ValueType ValueType::f32Type(Primitive::f32Primitive);
	const ValueType ValueType::f64Type(Primitive::f64Primitive);
	const ValueType ValueType::boolType(Primitive::boolPrimitive);
	const ValueType ValueType::charType(Primitive::charPrimitive);
	const ValueType ValueType::stringType(Primitive::stringPrimitive);

	bool ValueType::canConvertTo(const ValueType& to) const
	{
		return &_entity == &to._entity;
	}

	std::ostream& operator<<(std::ostream& out, const ValueType& type)
	{
		out << '`';
		out << type._entity.name();
		out << '`';

		return out;
	}
}
