#ifndef PARKA_UTIL_FLOAT_HPP
#define PARKA_UTIL_FLOAT_HPP

#include "parka/util/Common.hpp"

namespace parka
{
	class Float
	{
		f64 _value;

	public:

		explicit Float(f64 value) : _value(value) {}
		explicit Float(f32 value) : _value(value) {}
		
		Float(Float&&) = default;
		Float(const Float&) = default;

		Float& operator=(Float&&) = default;
		Float& operator=(const Float&) = default;

		// Binary operators
		friend Float operator+(const Float& left, const Float& right);
		friend Float operator-(const Float& left, const Float& right);
		friend Float operator*(const Float& left, const Float& right);
		friend Float operator/(const Float& left, const Float& right);
		friend bool operator<(const Float& left, const Float& right);
		friend bool operator>(const Float& left, const Float& right);
		friend bool operator<=(const Float& left, const Float& right);
		friend bool operator>=(const Float& left, const Float& right);
		friend bool operator==(const Float& left, const Float& right);
		friend bool operator!=(const Float& left, const Float& right);

		// Assignment operators
		Float& operator+=(const Float& other);
		Float& operator-=(const Float& other);
		Float& operator*=(const Float& other);
		Float& operator/=(const Float& other);

		explicit operator f32() const { return _value; }
		explicit operator f64() const { return _value; }
		operator bool() const { return _value != 0.0; }

		friend std::ostream& operator<<(std::ostream& out, const Float& number);
	};
}

#endif
