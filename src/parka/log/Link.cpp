#include "parka/log/Link.hpp"
#include "parka/log/Color.hpp"
#include <cassert>

namespace parka
{
	std::ostream& operator<<(std::ostream& out, const Link& link)
	{
		out << Color::Blue << "\033]8;;" << link._url << "\033\\" << link._text << "\033]8;;\033\\" << Color::Reset;

		return out;
	}
}
