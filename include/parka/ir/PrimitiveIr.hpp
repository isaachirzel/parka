#ifndef PARKA_IR_PRIMITIVE_IR_HPP
#define PARKA_IR_PRIMITIVE_IR_HPP

#include "parka/enum/PrimitiveType.hpp"
#include "parka/ir/EntityIr.hpp"
#include "parka/ir/InvalidTypeIr.hpp"
#include "parka/ir/TypeIr.hpp"
#include "parka/util/String.hpp"

namespace parka::ir
{
	class PrimitiveIr: public EntityIr, public TypeIr
	{
		String _symbol;
		PrimitiveType _primitiveType;

	public:

		static PrimitiveIr voidPrimitive;
		static PrimitiveIr integerPrimitive;
		static PrimitiveIr u8Primitive;
		static PrimitiveIr u16Primitive;
		static PrimitiveIr u32Primitive;
		static PrimitiveIr u64Primitive;
		static PrimitiveIr i8Primitive;
		static PrimitiveIr i16Primitive;
		static PrimitiveIr i32Primitive;
		static PrimitiveIr i64Primitive;
		static PrimitiveIr floatPrimitive;
		static PrimitiveIr f32Primitive;
		static PrimitiveIr f64Primitive;
		static PrimitiveIr boolPrimitive;
		static PrimitiveIr charPrimitive;
		static PrimitiveIr stringPrimitive;

	private:

		PrimitiveIr(PrimitiveType primitiveType);
		PrimitiveIr(PrimitiveIr&&) = delete;
		PrimitiveIr(const PrimitiveIr&) = delete;

	public:

		std::ostream& printType(std::ostream&) const;

		const String& symbol() const { return _symbol; }
		const TypeIr& type() const { return InvalidTypeIr::typeNameType; }
		const auto& primitiveType() const { return _primitiveType; }

		friend std::ostream& operator<<(std::ostream& out, const PrimitiveIr& primitive);
	};
}

#endif
