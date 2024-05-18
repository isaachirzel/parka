#include "parka/util/Integer.hpp"

namespace parka
{
	Integer::Integer(i64 value):
		_value(value)
	{}

	Integer operator+(const Integer& left, const Integer& right)
	{
		return left._value + right._value;
	}

	Integer operator-(const Integer& left, const Integer& right)
	{
		return left._value - right._value;
	}

	Integer operator*(const Integer& left, const Integer& right)
	{
		return left._value * right._value;
	}

	Integer operator/(const Integer& left, const Integer& right)
	{
		return left._value / right._value;
	}

	Integer operator%(const Integer& left, const Integer& right)
	{
		return left._value % right._value;
	}

	Integer operator|(const Integer& left, const Integer& right)
	{
		return left._value | right._value;
	}

	Integer operator^(const Integer& left, const Integer& right)
	{
		return left._value ^ right._value;
	}

	Integer operator&(const Integer& left, const Integer& right)
	{
		return left._value & right._value;
	}

	Integer operator<<(const Integer& left, const Integer& right)
	{
		return left._value < right._value;
	}

	Integer operator>>(const Integer& left, const Integer& right)
	{
		return left._value > right._value;
	}

	bool operator<(const Integer& left, const Integer& right)
	{
		return left._value < right._value;
	}

	bool operator>(const Integer& left, const Integer& right)
	{
		return left._value > right._value;
	}

	bool operator<=(const Integer& left, const Integer& right)
	{
		return left._value <= right._value;
	}

	bool operator>=(const Integer& left, const Integer& right)
	{
		return left._value >= right._value;
	}

	bool operator==(const Integer& left, const Integer& right)
	{
		return left._value == right._value;
	}

	bool operator!=(const Integer& left, const Integer& right)
	{
		return left._value != right._value;
	}

	Integer::operator i8()
	{
		return (i8)_value;
	}

	Integer::operator i16()
	{
		return (i16)_value;
	}

	Integer::operator i32()
	{
		return (i32)_value;
	}

	Integer::operator i64()
	{
		return (i64)_value;
	}

	Integer::operator u8()
	{
		return (u8)_value;
	}

	Integer::operator u16()
	{
		return (u16)_value;
	}

	Integer::operator u32()
	{
		return (u32)_value;
	}

	Integer::operator u64()
	{
		return (u64)_value;
	}

	std::ostream& operator<<(std::ostream& out, const Integer integer)
	{
		out << integer._value;

		return out;
	}
}
