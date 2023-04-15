#include "parka/log/Link.hpp"
#include "parka/log/Color.hpp"

namespace parka
{
	std::ostream& operator<<(std::ostream& out, const Link& link)
	{
		out << Color::Blue.code() << "\033]8;;" << link._url << "\033\\" << link._text << "\033]8;;\033\\" << Color::Reset.code();

		return out;
	}
}
