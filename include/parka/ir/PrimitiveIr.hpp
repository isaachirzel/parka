#ifndef PARKA_AST_PRIMITIVE_HPP
#define PARKA_AST_PRIMITIVE_HPP

#include "parka/enum/PrimitiveType.hpp"
#include "parka/ir/LValueIr.hpp"
#include "parka/ir/TypeIr.hpp"
#include "parka/symbol/Resolvable.hpp"
#include "parka/symbol/SymbolTable.hpp"

namespace parka::ir
{
	class PrimitiveIr: public TypeBaseIr, public Resolvable, public LValueIr
	{
		String _name;
		u32 _size;
		PrimitiveType _type;

	public:

		static PrimitiveIr voidPrimitive;
		static PrimitiveIr u8Primitive;
		static PrimitiveIr u16Primitive;
		static PrimitiveIr u32Primitive;
		static PrimitiveIr u64Primitive;
		static PrimitiveIr i8Primitive;
		static PrimitiveIr i16Primitive;
		static PrimitiveIr i32Primitive;
		static PrimitiveIr i64Primitive;
		static PrimitiveIr f32Primitive;
		static PrimitiveIr f64Primitive;
		static PrimitiveIr boolPrimitive;
		static PrimitiveIr charPrimitive;
		static PrimitiveIr stringPrimitive;
		static PrimitiveIr* entries[];
		static const usize entryCount;

	private:

		PrimitiveIr(const char *name, PrimitiveType type, u32 size);

	public:

		PrimitiveIr(PrimitiveIr&&) = default;
		PrimitiveIr(const PrimitiveIr&) = delete;

		SymbolTable* symbolTable() { return nullptr; }
		PrimitiveIr *resolve() { return this; }
		const TypeIr& type() const { return TypeIr::typeNameType; }
		const String& symbol() const { return _name; }
		const String& name() const { return _name; }
		const auto& primitiveType() const { return _type; }
		const auto& size() const { return _size; }
	};
}

#endif
