#ifndef PARKA_UTIL_INTEGER_HPP
#define PARKA_UTIL_INTEGER_HPP

#include "parka/util/Common.hpp"

namespace parka
{
	class Integer
	{
		i64 _value;

	public:

		explicit Integer(u8 value): _value(value) {}
		explicit Integer(u16 value): _value(value) {}
		explicit Integer(u32 value): _value(value) {}
		explicit Integer(u64 value): _value(value) {}
		explicit Integer(i8 value): _value(value) {}
		explicit Integer(i16 value): _value(value) {}
		explicit Integer(i32 value): _value(value) {}
		explicit Integer(i64 value): _value(value) {}
		Integer(Integer&&) = default;
		Integer(const Integer&) = default;
		Integer& operator=(Integer&&) = default;
		Integer& operator=(const Integer&) = default;

		// Binary operators
		friend Integer operator+(const Integer& left, const Integer& right);
		friend Integer operator-(const Integer& left, const Integer& right);
		friend Integer operator*(const Integer& left, const Integer& right);
		friend Integer operator/(const Integer& left, const Integer& right);
		friend Integer operator%(const Integer& left, const Integer& right);
		friend Integer operator|(const Integer& left, const Integer& right);
		friend Integer operator^(const Integer& left, const Integer& right);
		friend Integer operator&(const Integer& left, const Integer& right);
		friend Integer operator<<(const Integer& left, const Integer& right);
		friend Integer operator>>(const Integer& left, const Integer& right);
		friend bool operator<(const Integer& left, const Integer& right);
		friend bool operator>(const Integer& left, const Integer& right);
		friend bool operator<=(const Integer& left, const Integer& right);
		friend bool operator>=(const Integer& left, const Integer& right);
		friend bool operator==(const Integer& left, const Integer& right);
		friend bool operator!=(const Integer& left, const Integer& right);

		// Assignment operators
		Integer& operator+=(const Integer& other);
		Integer& operator-=(const Integer& other);
		Integer& operator*=(const Integer& other);
		Integer& operator/=(const Integer& other);
		Integer& operator%=(const Integer& other);
		Integer& operator<<=(const Integer& other);
		Integer& operator>>=(const Integer& other);
		Integer& operator|=(const Integer& other);
		Integer& operator^=(const Integer& other);
		Integer& operator&=(const Integer& other);
		
		explicit operator i8() const;
		explicit operator i16() const;
		explicit operator i32() const;
		explicit operator i64() const;
		explicit operator u8() const;
		explicit operator u16() const;
		explicit operator u32() const;
		explicit operator u64() const;
		// operator bool() const;

		friend std::ostream& operator<<(std::ostream& out, const Integer integer);
	};
}

#endif
