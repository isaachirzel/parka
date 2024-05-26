#include "parka/ir/FloatPrimitiveIr.hpp"

namespace parka::ir
{
	FloatPrimitiveIr FloatPrimitiveIr::floatPrimitive("float", 8);
	FloatPrimitiveIr FloatPrimitiveIr::f32Primitive("f32", 4);
	FloatPrimitiveIr FloatPrimitiveIr::f64Primitive("f64", 8);

	FloatPrimitiveIr::FloatPrimitiveIr(const char *name, u8 size):
		TypeIr(TypeCategory::Float),
		LValueIr(ResolvableType::Primitive),
		_name(name),
		_size(size)
	{}

	std::ostream& FloatPrimitiveIr::printType(std::ostream& out) const
	{
		out << _name;

		return out;
	}
}
