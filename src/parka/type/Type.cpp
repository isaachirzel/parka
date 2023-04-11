#include "parka/syntax/AdditiveExpressionSyntax.hpp"
#include "parka/syntax/LiteralSyntax.hpp"
#include "parka/syntax/FunctionSyntax.hpp"
#include "parka/syntax/PrimitiveSyntax.hpp"
#include "parka/syntax/TypeAnnotationSyntax.hpp"
#include "parka/type/Type.hpp"
#include "parka/repository/Storage.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	const Type Type::voidType(Storage::voidId);
	const Type Type::u8Type(Storage::u8Id);
	const Type Type::u16Type(Storage::u16Id);
	const Type Type::u32Type(Storage::u32Id);
	const Type Type::u64Type(Storage::u64Id);
	const Type Type::i8Type(Storage::i8Id);
	const Type Type::i16Type(Storage::i16Id);
	const Type Type::i32Type(Storage::i32Id);
	const Type Type::i64Type(Storage::i64Id);
	const Type Type::f32Type(Storage::f32Id);
	const Type Type::f64Type(Storage::f64Id);
	const Type Type::boolType(Storage::boolId);
	const Type Type::charType(Storage::charId);
	const Type Type::stringType(Storage::stringId);

	String Type::getName() const
	{
		auto& entity = Storage::get(_entityId);

		return entity.identifier();
	}

	bool Type::canConvertTo(const Type& to)
	{
		return _entityId == to.entityId();
	}

	std::ostream& operator<<(std::ostream& out, const Type& type)
	{
		// output symbol
		auto& entity = Storage::get(type.entityId());
		const auto& identifier = entity.identifier();

		out << '`' << identifier << '`';

		return out;
	}
}
