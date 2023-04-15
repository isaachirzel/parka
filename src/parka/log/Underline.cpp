#include "parka/log/Underline.hpp"
#include "parka/log/Margin.hpp"
#include "parka/util/Print.hpp"
#include <iterator>

namespace parka
{
	std::ostream& operator<<(std::ostream& out, const Underline& underline)
	{
		out << Margin();
		// TODO: Handle tabs
		auto iterator = std::ostream_iterator<char>(out);

		std::fill_n(iterator, underline._preLength, ' ');
		std::fill_n(iterator, underline._length, '~');

		out << '\n';

		return out;
	}
}
