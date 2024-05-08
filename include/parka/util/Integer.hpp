#ifndef PARKA_UTIL_INTEGER_HPP
#define PARKA_UTIL_INTEGER_HPP

#include "parka/util/Common.hpp"

namespace parka
{
	class Integer
	{
		i64 _value;

	public:

		Integer(i64 value);
		Integer(Integer&&) = default;
		Integer(const Integer&) = default;

		Integer& operator=(Integer&&) = default;
		Integer& operator=(const Integer&) = default;

		friend Integer operator+(const Integer& left, const Integer& right);
		friend Integer operator-(const Integer& left, const Integer& right);
		friend Integer operator*(const Integer& left, const Integer& right);
		friend Integer operator/(const Integer& left, const Integer& right);
		
		operator i8();
		operator i16();
		operator i32();
		operator i64();
		operator u8();
		operator u16();
		operator u32();
		operator u64();

		friend std::ostream& operator<<(std::ostream& out, const Integer integer);
	};
}

#endif
