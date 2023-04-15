#include "parka/util/StringView.hpp"

namespace parka
{
	std::ostream& operator<<(std::ostream& out, const StringView& text)
	{
		out.write(text._ptr, text._length);

		return out;
	}
}
