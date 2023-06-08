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

		Primitive(const char *identifier, PrimitiveType type, u32 size) :
		_identifier(identifier),
		_type(type),
		_size(size)
		{}

		static Array<const Primitive*> initPrimitives();

	public:

		static const Primitive voidPrimitive;
		static const Primitive u8Primitive;
		static const Primitive u16Primitive;
		static const Primitive u32Primitive;
		static const Primitive u64Primitive;
		static const Primitive i8Primitive;
		static const Primitive i16Primitive;
		static const Primitive i32Primitive;
		static const Primitive i64Primitive;
		static const Primitive f32Primitive;
		static const Primitive f64Primitive;
		static const Primitive boolPrimitive;
		static const Primitive charPrimitive;
		static const Primitive stringPrimitive;


		static const Array<const Primitive*> primitives;

	public:

		Primitive(Primitive&&) = default;
		Primitive(const Primitive&) = delete;

		const String& identifier() const { return _identifier; }
		EntityType type() const { return EntityType::Primitive; }
		const auto& primitiveType() const { return _type; }
		const auto& size() const { return _size; }
	};
}

#endif
