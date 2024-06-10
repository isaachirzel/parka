#include "parka/file/Snippet.hpp"
#include <algorithm>

namespace parka
{
	Snippet::Snippet(const Position& position, u32 length):
		_position(position),
		_length(length)
	{}

	Snippet& Snippet::operator=(const Snippet& other)
	{
		_position = other._position;
		_length = other._length;

		return *this;
	}

	Snippet Snippet::operator+(const Snippet& other) const
	{
		assert(&_position.file() == &other._position.file());

		const auto& firstSnippet = _position <= other._position
			? *this
			: other;
		const auto position = firstSnippet._position;
		const auto thisEnd = _position.index() + _length;
		const auto otherEnd = other._position.index() + other._length;
		const auto end = std::max(thisEnd, otherEnd);
		const auto length = end - position.index();
		const auto snippet = Snippet(position, length);

		return snippet;
	}
	
	bool Snippet::operator==(const Snippet& other) const
	{
		return _position == other._position && _length == other._length;
	}

	bool Snippet::operator!=(const Snippet& other) const
	{
		return !(*this == other);
	}

	std::ostream& operator<<(std::ostream& out, const Snippet& snippet)
	{
		const auto *start = snippet.begin();
		
		out.write(start, snippet._length);

		return out;
	}
}
