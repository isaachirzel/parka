#include "parka/file/Snippet.hpp"
#include "parka/log/Log.hpp"
#include "parka/util/SourceLocation.hpp"

#include <sstream>

namespace parka
{
	Snippet::Snippet(const File& file, usize index, usize length) :
	_file(file),
	_index(index),
	_length(length)
	{}

	Snippet Snippet::operator+(const Snippet& other) const
	{
		assert(&_file == &other._file);

		const auto thisEnd = _index + _length;
		const auto otherEnd = other._index + other._length;
		const auto end = thisEnd >= otherEnd
			? thisEnd
			: otherEnd;
		const auto index = _index >= other._index
			? other._index
			: _index;
		auto snippet = Snippet(_file, index, end - index);

		return snippet;
	}
	
	bool Snippet::operator==(const Snippet& other) const
	{
		const auto isSame = &_file == &other._file
			&& _index == other._index
			&& _length == other._length;

		return isSame;
	}

	std::ostream& operator<<(std::ostream& out, const Snippet& snippet)
	{
		const auto *start = snippet.begin();
		
		out.write(start, snippet._length);

		return out;
	}
}
