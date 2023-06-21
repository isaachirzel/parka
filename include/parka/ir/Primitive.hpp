#ifndef PARKA_AST_PRIMITIVE_HPP
#define PARKA_AST_PRIMITIVE_HPP

#include "parka/ast/Entity.hpp"
#include "parka/symbol/Resolvable.hpp"
#include "parka/symbol/Resolvable.hpp"
#include "parka/util/Array.hpp"

namespace parka::ir
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

	class Primitive : public Resolvable
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

		String getSymbol() const { return _name; }
		const String& symbol() const { return _name; }
		const String& name() const { return _name; }
		const ValueType *valueType() const;
		const auto& primitiveType() const { return _type; }
		const auto& size() const { return _size; }
	};
}

#endif
