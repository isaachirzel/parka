#ifndef PARKA_FILE_SNIPPET_HPP
#define PARKA_FILE_SNIPPET_HPP

#include "parka/Token.hpp"
#include "parka/file/File.hpp"
#include "parka/log/Color.hpp"
#include "parka/util/Common.hpp"
#include <ostream>

// TODO: Rename to Snippet and add one to each expression type

namespace parka
{
	class Snippet
	{
		FilePosition _position;
		usize _length;

	public:

		Snippet(const Token& token) :
		_position(token.position()),
		_length(token.length())
		{}
		Snippet(const File& file, usize index, usize length) :
		_position(file, index),
		_length(length)
		{}
		Snippet(Snippet&&) = default;
		Snippet(const Snippet&) = default;

		const auto *begin() const { return _position.ptr(); }
		const auto *end() const { return _position.ptr() + _length; }
		const auto& position() const { return _position; }
		const auto& length() const { return _length; }

		friend std::ostream& operator<<(std::ostream& out, const Snippet& snippet);
	};
}

#endif
