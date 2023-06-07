#include "parka/syntax/AdditiveExpressionSyntax.hpp"
#include "parka/syntax/LiteralSyntax.hpp"
#include "parka/syntax/FunctionSyntax.hpp"
#include "parka/intrinsic/Primitive.hpp"
#include "parka/syntax/TypeAnnotationSyntax.hpp"
#include "parka/type/ValueType.hpp"

#include "parka/util/Print.hpp"

namespace parka
{
	const ValueType ValueType::voidType(EntitySyntaxId::voidId);
	const ValueType ValueType::u8Type(EntitySyntaxId::u8Id);
	const ValueType ValueType::u16Type(EntitySyntaxId::u16Id);
	const ValueType ValueType::u32Type(EntitySyntaxId::u32Id);
	const ValueType ValueType::u64Type(EntitySyntaxId::u64Id);
	const ValueType ValueType::i8Type(EntitySyntaxId::i8Id);
	const ValueType ValueType::i16Type(EntitySyntaxId::i16Id);
	const ValueType ValueType::i32Type(EntitySyntaxId::i32Id);
	const ValueType ValueType::i64Type(EntitySyntaxId::i64Id);
	const ValueType ValueType::f32Type(EntitySyntaxId::f32Id);
	const ValueType ValueType::f64Type(EntitySyntaxId::f64Id);
	const ValueType ValueType::boolType(EntitySyntaxId::boolId);
	const ValueType ValueType::charType(EntitySyntaxId::charId);
	const ValueType ValueType::stringType(EntitySyntaxId::stringId);

	String ValueType::getName() const
	{
		auto& entity = *_entityId;

		return entity.identifier();
	}

	bool ValueType::canConvertTo(const ValueType& to)
	{
		return _entityId == to.entityId();
	}

	std::ostream& operator<<(std::ostream& out, const ValueType& type)
	{
		// output symbol
		auto& entity = *type.entityId();
		const auto& identifier = entity.identifier();

		out << '`' << identifier << '`';

		return out;
	}
}
