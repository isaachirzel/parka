#ifndef PARKA_IR_FLOAT_PRIMITIVE_IR_HPP
#define PARKA_IR_FLOAT_PRIMITIVE_IR_HPP

#include "parka/ir/LValueIr.hpp"
#include "parka/ir/TypeBaseIr.hpp"

namespace parka::ir
{
	class FloatPrimitiveIr: public TypeBaseIr, public LValueIr
	{
		String _name;
		u8 _size;

	public:

		static FloatPrimitiveIr f32Primitive;
		static FloatPrimitiveIr f64Primitive;

	private:

		FloatPrimitiveIr(const char *name, u8 size);
		FloatPrimitiveIr(FloatPrimitiveIr&&) = default;
		FloatPrimitiveIr(const FloatPrimitiveIr&) = delete;

	public:

		const TypeIr& type() const { return TypeIr::typeNameType; }
		const String& symbol() const { return _name; }
		const auto& size() const { return _size; }
	};
}

#endif
