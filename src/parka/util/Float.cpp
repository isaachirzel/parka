#include "parka/util/Float.hpp"

namespace parka
{
	Float::Float(f64 value):
		_value(value)
	{}

	Float operator+(const Float& left, const Float& right)
	{
		return left._value + right._value;
	}

	Float operator-(const Float& left, const Float& right)
	{
		return left._value - right._value;
	}

	Float operator*(const Float& left, const Float& right)
	{
		return left._value * right._value;
	}

	Float operator/(const Float& left, const Float& right)
	{
		return left._value / right._value;
	}
}