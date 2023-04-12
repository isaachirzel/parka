#include "parka/intrinsic/Primitive.hpp"

namespace parka
{
	const EntitySyntaxId Primitive::voidId(EntityType::Primitive, 0);
	const EntitySyntaxId Primitive::u8Id(EntityType::Primitive, 1);
	const EntitySyntaxId Primitive::u16Id(EntityType::Primitive, 2);
	const EntitySyntaxId Primitive::u32Id(EntityType::Primitive, 3);
	const EntitySyntaxId Primitive::u64Id(EntityType::Primitive, 4);
	const EntitySyntaxId Primitive::i8Id(EntityType::Primitive, 5);
	const EntitySyntaxId Primitive::i16Id(EntityType::Primitive, 6);
	const EntitySyntaxId Primitive::i32Id(EntityType::Primitive, 7);
	const EntitySyntaxId Primitive::i64Id(EntityType::Primitive, 8);
	const EntitySyntaxId Primitive::f32Id(EntityType::Primitive, 9);
	const EntitySyntaxId Primitive::f64Id(EntityType::Primitive, 10);
	const EntitySyntaxId Primitive::boolId(EntityType::Primitive, 11);
	const EntitySyntaxId Primitive::charId(EntityType::Primitive, 12);
	const EntitySyntaxId Primitive::stringId(EntityType::Primitive, 13);

	Array<Primitive> Primitive::primitives(14);

	void Primitive::initializeAll()
	{
		primitives.push({ "void", PrimitiveType::Void, 0 });
		primitives.push({ "u8", PrimitiveType::UnsignedInteger, 1 });
		primitives.push({ "u16", PrimitiveType::UnsignedInteger, 2 });
		primitives.push({ "u32", PrimitiveType::UnsignedInteger, 4 });
		primitives.push({ "u64", PrimitiveType::UnsignedInteger, 8 });
		primitives.push({ "i8", PrimitiveType::SignedInteger, 1 });
		primitives.push({ "i16", PrimitiveType::SignedInteger, 2 });
		primitives.push({ "i32", PrimitiveType::SignedInteger, 4 });
		primitives.push({ "i64", PrimitiveType::SignedInteger, 8 });
		primitives.push({ "f32", PrimitiveType::FloatingPoint, 4 });
		primitives.push({ "f64", PrimitiveType::FloatingPoint, 8 });
		primitives.push({ "bool", PrimitiveType::Boolean, 1 });
		primitives.push({ "char", PrimitiveType::Character, 1 });
		primitives.push({ "string", PrimitiveType::String, 0 });
	}

	void Primitive::declareAll(Table<String, EntitySyntaxId>& globalSymbols)
	{
		usize index = 0;

		for (const auto& primitive: primitives)
		{
			globalSymbols.emplace(primitive.identifier(), EntitySyntaxId { EntityType::Primitive, index });
			
			index += 1;
		}
	}
}
