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

	bool operator<(const Float& left, const Float& right)
	{
		return left._value < right._value;
	}

	bool operator>(const Float& left, const Float& right)
	{
		return left._value > right._value;
	}
	
	bool operator<=(const Float& left, const Float& right)
	{
		return left._value <= right._value;
	}

	bool operator>=(const Float& left, const Float& right)
	{
		return left._value >= right._value;
	}

	bool operator==(const Float& left, const Float& right)
	{
		return left._value == right._value;
	}

	bool operator!=(const Float& left, const Float& right)
	{
		return left._value != right._value;
	}
	
	Float::operator f32()
	{
		return (f32)_value;
	}

	Float::operator f64()
	{
		return (f64)_value;
	}
	
	std::ostream& operator<<(std::ostream& out, const Float& number)
	{
		out << number._value;

		return out;
	}
}