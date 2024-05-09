#ifndef PARKA_AST_PRIMITIVE_HPP
#define PARKA_AST_PRIMITIVE_HPP

#include "parka/ir/LValueIr.hpp"
#include "parka/ir/TypeIr.hpp"
#include "parka/symbol/Resolvable.hpp"
#include "parka/symbol/Resolvable.hpp"

namespace parka::ir
{
	enum class PrimitiveType: u8
	{
		Void,
		UnsignedInteger,
		SignedInteger,
		FloatingPoint,
		Boolean,
		Character,
		String
	};

	class Primitive: public TypeBase, public Resolvable, public LValueIr
	{
		String _name;
		u32 _size;
		PrimitiveType _type;

	public:

		static Primitive entries[];
		static const usize entryCount;
		static Primitive& voidPrimitive;
		static Primitive& u8Primitive;
		static Primitive& u16Primitive;
		static Primitive& u32Primitive;
		static Primitive& u64Primitive;
		static Primitive& i8Primitive;
		static Primitive& i16Primitive;
		static Primitive& i32Primitive;
		static Primitive& i64Primitive;
		static Primitive& f32Primitive;
		static Primitive& f64Primitive;
		static Primitive& boolPrimitive;
		static Primitive& charPrimitive;
		static Primitive& stringPrimitive;

	private:

		Primitive(const char *name, PrimitiveType type, u32 size);

	public:

		Primitive(Primitive&&) = default;
		Primitive(const Primitive&) = delete;

		LValueIr *resolve() { return this; }
		const Type& type() const { return Type::typeNameType; }
		const String& symbol() const { return _name; }
		const String& name() const { return _name; }
		const auto& primitiveType() const { return _type; }
		const auto& size() const { return _size; }
	};
}

#endif
