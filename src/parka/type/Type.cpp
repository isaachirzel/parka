#include "parka/syntax/AdditiveExpressionSyntax.hpp"
#include "parka/syntax/LiteralSyntax.hpp"
#include "parka/syntax/FunctionSyntax.hpp"
#include "parka/intrinsic/Primitive.hpp"
#include "parka/syntax/TypeAnnotationSyntax.hpp"
#include "parka/type/Type.hpp"
#include "parka/repository/SyntaxRepository.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	const Type Type::voidType(Primitive::voidId);
	const Type Type::u8Type(Primitive::u8Id);
	const Type Type::u16Type(Primitive::u16Id);
	const Type Type::u32Type(Primitive::u32Id);
	const Type Type::u64Type(Primitive::u64Id);
	const Type Type::i8Type(Primitive::i8Id);
	const Type Type::i16Type(Primitive::i16Id);
	const Type Type::i32Type(Primitive::i32Id);
	const Type Type::i64Type(Primitive::i64Id);
	const Type Type::f32Type(Primitive::f32Id);
	const Type Type::f64Type(Primitive::f64Id);
	const Type Type::boolType(Primitive::boolId);
	const Type Type::charType(Primitive::charId);
	const Type Type::stringType(Primitive::stringId);

	String Type::getName() const
	{
		auto& entity = SyntaxRepository::get(_entityId);

		return entity.identifier();
	}

	bool Type::canConvertTo(const Type& to)
	{
		return _entityId == to.entityId();
	}

	std::ostream& operator<<(std::ostream& out, const Type& type)
	{
		// output symbol
		auto& entity = SyntaxRepository::get(type.entityId());
		const auto& identifier = entity.identifier();

		out << '`' << identifier << '`';

		return out;
	}
}
