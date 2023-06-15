#include "parka/file/Snippet.hpp"
#include "parka/log/Log.hpp"
#include "parka/util/SourceLocation.hpp"

#include <sstream>

namespace parka
{
	Snippet::Snippet(const File& file, usize index, usize length) :
	_position(file, index),
	_length(length)
	{}

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

	String Snippet::text() const
	{
		return String(_position.ptr(), _length);
	}

	String Snippet::substr(usize pos, usize length) const
	{
		assert(pos < _length);
		assert(pos + length < _length);

		return String(_position.ptr() + pos, length);
	}

	bool Snippet::operator==(const Snippet& other) const
	{
		return _position == other._position && _length == other._length;
	}

	std::ostream& operator<<(std::ostream& out, const Snippet& snippet)
	{
		const auto *start = snippet.begin();
		
		out.write(start, snippet._length);

		return out;
	}
}
