#ifndef PARKA_UTIL_FLOAT_HPP
#define PARKA_UTIL_FLOAT_HPP

#include "parka/ir/TypeBaseIr.hpp"
#include "parka/util/Common.hpp"
#include "parka/util/String.hpp"

namespace parka
{
	class Float: public ir::TypeBaseIr
	{
		f64 _value;

		static const String _symbol;

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
		friend bool operator<(const Float& left, const Float& right);
		friend bool operator>(const Float& left, const Float& right);
		friend bool operator<=(const Float& left, const Float& right);
		friend bool operator>=(const Float& left, const Float& right);
		friend bool operator==(const Float& left, const Float& right);
		friend bool operator!=(const Float& left, const Float& right);

		operator f32();
		operator f64();

		const String& symbol() const { return _symbol; }

		friend std::ostream& operator<<(std::ostream& out, const Float& number);
	};
}

#endif
