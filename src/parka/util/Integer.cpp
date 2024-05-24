#include "parka/util/Integer.hpp"

namespace parka
{
	Integer operator+(const Integer& left, const Integer& right)
	{
		return Integer(left._value + right._value);
	}

	Integer operator-(const Integer& left, const Integer& right)
	{
		return Integer(left._value - right._value);
	}

	Integer operator*(const Integer& left, const Integer& right)
	{
		return Integer(left._value * right._value);
	}

	Integer operator/(const Integer& left, const Integer& right)
	{
		return Integer(left._value / right._value);
	}

	Integer operator%(const Integer& left, const Integer& right)
	{
		return Integer(left._value % right._value);
	}

	Integer operator|(const Integer& left, const Integer& right)
	{
		return Integer(left._value | right._value);
	}

	Integer operator^(const Integer& left, const Integer& right)
	{
		return Integer(left._value ^ right._value);
	}

	Integer operator&(const Integer& left, const Integer& right)
	{
		return Integer(left._value & right._value);
	}

	Integer operator<<(const Integer& left, const Integer& right)
	{
		return Integer(left._value < right._value);
	}

	Integer operator>>(const Integer& left, const Integer& right)
	{
		return Integer(left._value > right._value);
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

	Integer& Integer::operator+=(const Integer& other)
	{
		_value += other._value;
		return *this;
	}

	Integer& Integer::operator-=(const Integer& other)
	{
		_value -= other._value;
		return *this;
	}

	Integer& Integer::operator*=(const Integer& other)
	{
		_value *= other._value;
		return *this;
	}

	Integer& Integer::operator/=(const Integer& other)
	{
		_value /= other._value;
		return *this;
	}

	Integer& Integer::operator%=(const Integer& other)
	{
		_value %= other._value;
		return *this;
	}

	Integer& Integer::operator<<=(const Integer& other)
	{
		_value <<= other._value;
		return *this;
	}

	Integer& Integer::operator>>=(const Integer& other)
	{
		_value >>= other._value;
		return *this;
	}

	Integer& Integer::operator|=(const Integer& other)
	{
		_value |= other._value;
		return *this;
	}

	Integer& Integer::operator^=(const Integer& other)
	{
		_value ^= other._value;
		return *this;
	}

	Integer& Integer::operator&=(const Integer& other)
	{
		_value &= other._value;
		return *this;
	}

	Integer::operator i8() const
	{
		return (i8)_value;
	}

	Integer::operator i16() const
	{
		return (i16)_value;
	}

	Integer::operator i32() const
	{
		return (i32)_value;
	}

	Integer::operator i64() const
	{
		return (i64)_value;
	}

	Integer::operator u8() const
	{
		return (u8)_value;
	}

	Integer::operator u16() const
	{
		return (u16)_value;
	}

	Integer::operator u32() const
	{
		return (u32)_value;
	}

	Integer::operator u64() const
	{
		return (u64)_value;
	}

	std::ostream& operator<<(std::ostream& out, const Integer integer)
	{
		out << integer._value;

		return out;
	}
}
