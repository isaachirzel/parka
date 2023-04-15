#ifndef PARKA_FILE_HIGHLIGHT_HPP
#define PARKA_FILE_HIGHLIGHT_HPP

#include "parka/Token.hpp"
#include "parka/file/File.hpp"
#include "parka/log/Color.hpp"
#include "parka/util/Common.hpp"
#include <ostream>

namespace parka
{
	class Highlight
	{
		FilePosition _position;
		usize _length;

	public:

		Highlight(const Token& token) :
		_position(token.position()),
		_length(token.length())
		{}
		Highlight(const File& file, usize index, usize length) :
		_position(file, index),
		_length(length)
		{}
		Highlight(Highlight&&) = default;
		Highlight(const Highlight&) = default;
		~Highlight() = default;


		const auto *begin() const { return _position.ptr(); }
		const auto *end() const { return _position.ptr() + _length; }
		const auto& position() const { return _position; }
		const auto& length() const { return _length; }

		friend std::ostream& operator<<(std::ostream& out, const Highlight& highlight);
	};
}

#endif
