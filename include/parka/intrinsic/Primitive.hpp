#ifndef PARKA_SYNTAX_PRIMITIVE_SYNTAX_HPP
#define PARKA_SYNTAX_PRIMITIVE_SYNTAX_HPP

#include "parka/enum/PrimitiveType.hpp"
#include "parka/repository/EntityContext.hpp"
#include "parka/syntax/EntitySyntax.hpp"
#include "parka/util/Array.hpp"
#include "parka/util/Common.hpp"
#include "parka/util/String.hpp"
#include "parka/util/Table.hpp"
#include "parka/util/View.hpp"

namespace parka
{
	class Primitive : public EntitySyntax, public EntityContext
	{
		String _identifier;
		PrimitiveType _type;
		u32 _size;

	public:

		static Primitive voidPrimitive;
		static Primitive u8Primitive;
		static Primitive u16Primitive;
		static Primitive u32Primitive;
		static Primitive u64Primitive;
		static Primitive i8Primitive;
		static Primitive i16Primitive;
		static Primitive i32Primitive;
		static Primitive i64Primitive;
		static Primitive f32Primitive;
		static Primitive f64Primitive;
		static Primitive boolPrimitive;
		static Primitive charPrimitive;
		static Primitive stringPrimitive;
		static const Array<Primitive*> primitives;

	private:

		static Array<Primitive*> initPrimitives();

		Primitive(const char *identifier, PrimitiveType type, u32 size) :
		_identifier(identifier),
		_type(type),
		_size(size)
		{}

	public:

		Primitive(Primitive&&) = default;
		Primitive(const Primitive&) = delete;

		const String& identifier() const { return _identifier; }
		EntityType entityType() const { return EntityType::Primitive; }
		const auto& primitiveType() const { return _type; }
		const auto& size() const { return _size; }
	};
}

#endif
