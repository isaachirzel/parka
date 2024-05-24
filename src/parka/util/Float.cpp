#include "parka/util/Float.hpp"

namespace parka
{
	Float operator+(const Float& left, const Float& right)
	{
		return Float(left._value + right._value);
	}

	Float operator-(const Float& left, const Float& right)
	{
		return Float(left._value - right._value);
	}

	Float operator*(const Float& left, const Float& right)
	{
		return Float(left._value * right._value);
	}

	Float operator/(const Float& left, const Float& right)
	{
		return Float(left._value / right._value);
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

	Float& Float::operator+=(const Float& other)
	{
		_value += other._value;
		return *this;
	}

	Float& Float::operator-=(const Float& other)
	{
		_value -= other._value;
		return *this;
	}

	Float& Float::operator*=(const Float& other)
	{
		_value *= other._value;
		return *this;
	}

	Float& Float::operator/=(const Float& other)
	{
		_value /= other._value;
		return *this;
	}
	
	std::ostream& operator<<(std::ostream& out, const Float& number)
	{
		out << number._value;

		return out;
	}
}