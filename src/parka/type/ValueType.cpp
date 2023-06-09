#include "parka/log/Log.hpp"
#include "parka/syntax/AdditiveExpressionSyntax.hpp"
#include "parka/syntax/LiteralSyntax.hpp"
#include "parka/syntax/FunctionSyntax.hpp"
#include "parka/intrinsic/Primitive.hpp"
#include "parka/syntax/TypeAnnotationSyntax.hpp"
#include "parka/type/ValueType.hpp"

namespace parka
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

	ValueType::ValueType(const EntityContext& entity) :
	_entity(entity)
	{}

	Optional<ValueType> ValueType::validate(const TypeAnnotationSyntax& syntax, SymbolTable& symbolTable)
	{
		const auto *entity = symbolTable.resolve(syntax.identifier());

		if (!entity)
			return {};

		auto result = ValueType(*entity);

		return result;
	}

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
