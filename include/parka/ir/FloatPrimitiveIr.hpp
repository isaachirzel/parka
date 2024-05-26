#ifndef PARKA_IR_FLOAT_PRIMITIVE_IR_HPP
#define PARKA_IR_FLOAT_PRIMITIVE_IR_HPP

#include "parka/ir/LValueIr.hpp"
#include "parka/ir/TypeIr.hpp"
#include "parka/ir/TypeNameIr.hpp"

namespace parka::ir
{
	class FloatPrimitiveIr: public TypeIr, public LValueIr
	{
		String _name;
		u8 _size;

	public:

		static FloatPrimitiveIr floatPrimitive;
		static FloatPrimitiveIr f32Primitive;
		static FloatPrimitiveIr f64Primitive;

	private:

		FloatPrimitiveIr(const char *name, u8 size);
		FloatPrimitiveIr(FloatPrimitiveIr&&) = default;
		FloatPrimitiveIr(const FloatPrimitiveIr&) = delete;

	public:

		std::ostream& printType(std::ostream& out) const;

		const TypeIr& type() const { return TypeNameIr::instance; }
		const String& symbol() const { return _name; }
		const auto& size() const { return _size; }
	};
}

#endif
