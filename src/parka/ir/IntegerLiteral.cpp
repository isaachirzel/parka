#include "parka/ir/IntegerLiteral.hpp"

namespace parka::ir
{
	static usize getSize(u64 value)
	{
		if (value > 0xFFFFFFFF)
			return sizeof(u64);

		if (value > 0x0000FFFF)
			return sizeof(u32);

		if (value > 0x000000FF)
			return sizeof(u16);

		return sizeof(u8);
	}
	
	IntegerLiteralIr::IntegerLiteralIr(u64 value):
		ExpressionIr(ExpressionType::IntegerLiteral),
		_value(value),
		_size(getSize(value))
	{}
}