#ifndef PARKA_SYNTAX_PRIMITIVE_SYNTAX_HPP
#define PARKA_SYNTAX_PRIMITIVE_SYNTAX_HPP

#include "parka/ast/Entity.hpp"
#include "parka/util/Array.hpp"

namespace parka
{
	enum class PrimitiveType : u8
	{
		Void,
		UnsignedInteger,
		SignedInteger,
		FloatingPoint,
		Boolean,
		Character,
		String
	};

	class Primitive : public EntitySyntax, public EntityContext
	{
		String _name;
		u32 _size;
		PrimitiveType _type;

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

		Primitive(const char *name, PrimitiveType type, u32 size);

	public:

		Primitive(Primitive&&) = default;
		Primitive(const Primitive&) = delete;

		EntityContext *context() { return this; }

		const String& name() const { return _name; }
		EntityType entityType() const { return EntityType::Primitive; }
		const auto& primitiveType() const { return _type; }
		const auto& size() const { return _size; }
	};
}

#endif
