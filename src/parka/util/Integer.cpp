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
}
