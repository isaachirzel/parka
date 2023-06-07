#include "parka/log/Highlight.hpp"
#include "parka/log/Log.hpp"
#include "parka/util/SourceLocation.hpp"

#include <sstream>

namespace parka
{
	usize getStartOfLine(const char *text, usize pos)
	{
		while (pos > 1)
		{
			if (text[pos - 1] == '\n')
				return pos;

			--pos;
		}

		return 0;
	}

	const char *getEndOfLine(const char *iter)
	{
		while (*iter)
		{
			if (*iter == '\n')
				break;
			iter += 1;
		}

		return iter;
	}

	std::ostream& operator<<(std::ostream& out, const Highlight& highlight)
	{
		const auto *start = highlight.begin();
		
		out.write(start, highlight._length);

		return out;
	}
}
