#include "parka/log/Underline.hpp"
#include "parka/log/Margin.hpp"
#include <iterator>

namespace parka
{
	std::ostream& operator<<(std::ostream& out, const Underline& underline)
	{
		out << Margin();
		
		auto iterator = std::ostream_iterator<char>(out);

		for (const auto& ch : underline._preText)
		{
			out << (ch == '\t' ? ch : ' ');
		}

		std::fill_n(iterator, underline._length, '~');

		out << '\n';

		return out;
	}
}
