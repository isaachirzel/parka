#include "parka/log/Log.hpp"
#include "parka/syntax/AdditiveExpressionSyntax.hpp"
#include "parka/syntax/LiteralSyntax.hpp"
#include "parka/syntax/FunctionSyntax.hpp"
#include "parka/intrinsic/Primitive.hpp"
#include "parka/syntax/TypeAnnotationSyntax.hpp"
#include "parka/type/ValueType.hpp"

namespace parka
{
	ValueType ValueType::voidType(Primitive::voidPrimitive);
	ValueType ValueType::u8Type(Primitive::u8Primitive);
	ValueType ValueType::u16Type(Primitive::u16Primitive);
	ValueType ValueType::u32Type(Primitive::u32Primitive);
	ValueType ValueType::u64Type(Primitive::u64Primitive);
	ValueType ValueType::i8Type(Primitive::i8Primitive);
	ValueType ValueType::i16Type(Primitive::i16Primitive);
	ValueType ValueType::i32Type(Primitive::i32Primitive);
	ValueType ValueType::i64Type(Primitive::i64Primitive);
	ValueType ValueType::f32Type(Primitive::f32Primitive);
	ValueType ValueType::f64Type(Primitive::f64Primitive);
	ValueType ValueType::boolType(Primitive::boolPrimitive);
	ValueType ValueType::charType(Primitive::charPrimitive);
	ValueType ValueType::stringType(Primitive::stringPrimitive);

	ValueType::ValueType(EntityContext& entity) :
	_entity(entity)
	{}

	bool ValueType::canConvertTo(const ValueType& to)
	{
		return &_entity == &to._entity;
	}

	std::ostream& operator<<(std::ostream& out, const ValueType& type)
	{
		log::notImplemented(here());
		// output symbol
		// auto& entity = *type.entityId();
		// const auto& identifier = entity.identifier();

		// out << '`' << identifier << '`';

		return out;
	}
}
