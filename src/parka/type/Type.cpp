#include "parka/syntax/AdditiveExpressionSyntax.hpp"
#include "parka/syntax/LiteralSyntax.hpp"
#include "parka/syntax/FunctionSyntax.hpp"
#include "parka/intrinsic/Primitive.hpp"
#include "parka/syntax/TypeAnnotationSyntax.hpp"
#include "parka/type/Type.hpp"

#include "parka/util/Print.hpp"

namespace parka
{
	const Type Type::voidType(EntitySyntaxId::voidId);
	const Type Type::u8Type(EntitySyntaxId::u8Id);
	const Type Type::u16Type(EntitySyntaxId::u16Id);
	const Type Type::u32Type(EntitySyntaxId::u32Id);
	const Type Type::u64Type(EntitySyntaxId::u64Id);
	const Type Type::i8Type(EntitySyntaxId::i8Id);
	const Type Type::i16Type(EntitySyntaxId::i16Id);
	const Type Type::i32Type(EntitySyntaxId::i32Id);
	const Type Type::i64Type(EntitySyntaxId::i64Id);
	const Type Type::f32Type(EntitySyntaxId::f32Id);
	const Type Type::f64Type(EntitySyntaxId::f64Id);
	const Type Type::boolType(EntitySyntaxId::boolId);
	const Type Type::charType(EntitySyntaxId::charId);
	const Type Type::stringType(EntitySyntaxId::stringId);

	String Type::getName() const
	{
		auto& entity = *_entityId;

		return entity.identifier();
	}

	bool Type::canConvertTo(const Type& to)
	{
		return _entityId == to.entityId();
	}

	std::ostream& operator<<(std::ostream& out, const Type& type)
	{
		// output symbol
		auto& entity = *type.entityId();
		const auto& identifier = entity.identifier();

		out << '`' << identifier << '`';

		return out;
	}
}
