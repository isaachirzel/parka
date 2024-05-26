#include "parka/ir/FloatPrimitiveIr.hpp"

namespace parka::ir
{
	FloatPrimitiveIr FloatPrimitiveIr::f32Primitive("f32", 4);
	FloatPrimitiveIr FloatPrimitiveIr::f64Primitive("f64", 8);

	FloatPrimitiveIr::FloatPrimitiveIr(const char *name, u8 size):
		LValueIr(ResolvableType::Primitive),
		_name(name),
		_size(size)
	{}	
}
