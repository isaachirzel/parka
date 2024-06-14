#include "parka/enum/ErrorCode.hpp"
#include "parka/util/Common.hpp"

namespace parka
{
	std::ostream& operator<<(std::ostream& out, ErrorCode code)
	{
		constexpr char zeroes [] = "0000";
		const auto value = static_cast<u16>(code);

		auto temp = value;
		u8 zeroCount = 0;

		while (temp < 1000)
		{
			temp *= 10;
			zeroCount += 1;
		}

		out << "PK";
		out.write(zeroes, zeroCount);
		out << value;

		return out;
	}
}
