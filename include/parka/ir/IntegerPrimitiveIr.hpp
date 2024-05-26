#ifndef PARKA_IR_INTEGER_PRIMITIVE_IR_HPP
#define PARKA_IR_INTEGER_PRIMITIVE_IR_HPP

#include "parka/ir/LValueIr.hpp"
#include "parka/ir/TypeIr.hpp"
#include "parka/ir/TypeNameIr.hpp"

namespace parka::ir
{
	class IntegerPrimitiveIr: public TypeIr, public LValueIr
	{
		String _name;
		bool _isSigned;
		u8 _size;

	public:

		static IntegerPrimitiveIr integerPrimitive;
		static IntegerPrimitiveIr u8Primitive;
		static IntegerPrimitiveIr u16Primitive;
		static IntegerPrimitiveIr u32Primitive;
		static IntegerPrimitiveIr u64Primitive;
		static IntegerPrimitiveIr i8Primitive;
		static IntegerPrimitiveIr i16Primitive;
		static IntegerPrimitiveIr i32Primitive;
		static IntegerPrimitiveIr i64Primitive;

	private:
	
		IntegerPrimitiveIr(const char *name, bool isSigned, u8 size);
		IntegerPrimitiveIr(IntegerPrimitiveIr&&) = default;
		IntegerPrimitiveIr(const IntegerPrimitiveIr&) = delete;

	public:

		std::ostream& printType(std::ostream& out) const;

		const TypeIr& type() const { return TypeNameIr::typeNameType; }
		const String& symbol() const { return _name; }
		const auto& isSigned() const { return _isSigned; }
		const auto& size() const { return _size; }
	};
}

#endif
