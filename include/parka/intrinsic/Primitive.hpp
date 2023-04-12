#ifndef PARKA_SYNTAX_PRIMITIVE_SYNTAX_HPP
#define PARKA_SYNTAX_PRIMITIVE_SYNTAX_HPP

#include "parka/enum/PrimitiveType.hpp"
#include "parka/repository/EntitySyntaxId.hpp"
#include "parka/syntax/EntitySyntax.hpp"
#include "parka/util/Common.hpp"
#include "parka/util/String.hpp"
#include "parka/util/Table.hpp"

namespace parka
{
	class Primitive : public EntitySyntax
	{
		String _identifier;
		PrimitiveType _type;
		u32 _size;

		Primitive(const char *identifier, PrimitiveType type, u32 size) :
		_identifier(identifier),
		_type(type),
		_size(size)
		{}

	public:

		static Array<Primitive> primitives;

		static const EntitySyntaxId voidId;
		static const EntitySyntaxId u8Id;
		static const EntitySyntaxId u16Id;
		static const EntitySyntaxId u32Id;
		static const EntitySyntaxId u64Id;
		static const EntitySyntaxId i8Id;
		static const EntitySyntaxId i16Id;
		static const EntitySyntaxId i32Id;
		static const EntitySyntaxId i64Id;
		static const EntitySyntaxId f32Id;
		static const EntitySyntaxId f64Id;
		static const EntitySyntaxId boolId;
		static const EntitySyntaxId charId;
		static const EntitySyntaxId stringId;

		static void initializeAll();
		static void declareAll(Table<String, EntitySyntaxId>& globalSymbols);

	public:

		Primitive(Primitive&&) = default;
		Primitive(const Primitive&) = delete;
		~Primitive() = default;

		const String& identifier() const { return _identifier; }
		EntityType type() const { return EntityType::Primitive; }
		const auto& primitiveType() const { return _type; }
		const auto& size() const { return _size; }
	};
}

#endif
