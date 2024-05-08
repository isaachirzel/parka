#ifndef PARKA_UTIL_FLOAT_HPP
#define PARKA_UTIL_FLOAT_HPP

#include "parka/util/Common.hpp"

namespace parka
{
	class Float
	{
		f64 _value;

	public:

		Float(f64 value);
		Float(Float&&) = default;
		Float(const Float&) = default;

		Float& operator=(Float&&) = default;
		Float& operator=(const Float&) = default;

		friend Float operator+(const Float& left, const Float& right);
		friend Float operator-(const Float& left, const Float& right);
		friend Float operator*(const Float& left, const Float& right);
		friend Float operator/(const Float& left, const Float& right);

		operator f32();
		operator f64();

		friend std::ostream& operator<<(std::ostream& out, const Float& number);
	};
}

#endif
