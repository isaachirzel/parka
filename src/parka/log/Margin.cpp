#include "parka/log/Margin.hpp"
#include "parka/log/Color.hpp"
#include <iterator>

namespace parka
{
	const int Margin::xIndex = std::ios_base::xalloc();

	usize getNumberWidth(usize number)
	{
		// TODO: get line count to make sure it doesn't overflow
		usize out = 1;
		
		while (number > 9)
		{
			out += 1;
			number /= 10;
		}

		return out;
	}

	std::ostream& operator<<(std::ostream& out, const Margin& margin)
	{
		out << Color::Blue;
		
		if (margin._lineNumber > 0)
		{
			out << std::setw(5) << margin._lineNumber;
		}
		else
		{
			std::fill_n(std::ostream_iterator<char>(out), 5, ' ');
		}

		out << " | ";
		out << Color::Reset;

		return out;
	}
}
