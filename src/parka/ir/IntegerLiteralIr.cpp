#include "parka/ir/IntegerLiteralIr.hpp"

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
	
	IntegerLiteralIr::IntegerLiteralIr(i64 value):
		ExpressionIr(ExpressionType::IntegerLiteral),
		_type(TypeIr::integerType),
		_value(value),
		_size(getSize(value))
	{}

	void IntegerLiteralIr::setType(TypeIr&& type)
	{
		_type = std::move(type);
	}
}