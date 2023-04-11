#ifndef PARKA_FILE_HIGHLIGHT_HPP
#define PARKA_FILE_HIGHLIGHT_HPP

#include "parka/util/Primitives.hpp"

namespace parka
{
	class Highlight
	{
		const File& _file;
		usize _index;
		usize _length;
		FilePosition _position;

	public:

		Highlight(const File& file, usize index, usize length) :
		_file(file),
		_index(index),
		_length(length),
		_position(file.getPosition(index))
		{}
		Highlight(Highlight&&) = default;
		Highlight(const Highlight&) = default;
		~Highlight() = default;

		const auto& file() const { return _file; }
		const auto& index() const { return _index; }
		const auto& length() const { return _length; }
		const auto& position() const { return _position; }
	};
}

#endif
