#include "parka/log/Link.hpp"
#include "parka/log/Color.hpp"

namespace parka::log
{
	std::ostream& operator<<(std::ostream& out, const Link& link)
	{
		out << Color::darkBlue << "\033]8;;" << link._url << "\033\\" << link._text << "\033]8;;\033\\" << Color::reset;

		return out;
	}
}
