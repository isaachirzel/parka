#ifndef PARKA_FILE_SNIPPET_HPP
#define PARKA_FILE_SNIPPET_HPP

#include "parka/file/File.hpp"
#include "parka/file/FilePosition.hpp"
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

		Snippet(const File& file, usize index, usize length);
		Snippet(Snippet&&) = default;
		Snippet(const Snippet&) = default;

		String text() const;
		String substr(usize pos, usize length) const;
		const char *ptr() const { return _position.ptr(); }
		const char *begin() const { return _position.ptr(); }
		const char *end() const { return _position.ptr() + _length; }
		const auto& position() const { return _position; }
		const auto& length() const { return _length; }

		bool operator==(const Snippet& other) const;
		const auto& operator[](usize index) const { return _position.file()[index]; }
		friend std::ostream& operator<<(std::ostream& out, const Snippet& snippet);
	};
}

#endif
