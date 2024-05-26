#include "parka/ir/IntegerPrimitiveIr.hpp"
#include "parka/ir/LValueIr.hpp"

namespace parka::ir
{
	IntegerPrimitiveIr IntegerPrimitiveIr::u8Primitive("u8", false, 1);
	IntegerPrimitiveIr IntegerPrimitiveIr::u16Primitive("u16", false, 2);
	IntegerPrimitiveIr IntegerPrimitiveIr::u32Primitive("u32", false, 4);
	IntegerPrimitiveIr IntegerPrimitiveIr::u64Primitive("u64", false, 8);
	IntegerPrimitiveIr IntegerPrimitiveIr::i8Primitive("i8", true, 1);
	IntegerPrimitiveIr IntegerPrimitiveIr::i16Primitive("i16", true, 2);
	IntegerPrimitiveIr IntegerPrimitiveIr::i32Primitive("i32", true, 4);
	IntegerPrimitiveIr IntegerPrimitiveIr::i64Primitive("i64", true, 8);

	IntegerPrimitiveIr::IntegerPrimitiveIr(const char *name, bool isSigned, u8 size):
		LValueIr(ResolvableType::Primitive),
		_name(name),
		_isSigned(isSigned),
		_size(size)
	{}
}
