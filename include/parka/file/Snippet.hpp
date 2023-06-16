#ifndef PARKA_FILE_SNIPPET_HPP
#define PARKA_FILE_SNIPPET_HPP

#include "parka/file/File.hpp"
#include "parka/util/Common.hpp"

#include <ostream>

// TODO: Rename to Snippet and add one to each expression type

namespace parka
{
	class Snippet
	{
		const File& _file;
		const usize _index;
		const usize _length;

	public:

		Snippet(const File& file, usize index, usize length);
		Snippet(const Snippet&) = default;

		String text() const { return _file.substr(_index, _length); }
		String substr(const usize index, const usize length) const { return _file.substr(_index + index, length); }
		usize line() const { return _file.getLine(_index); }
		usize col() const { return _file.getCol(_index); }

		const char *ptr() const { return &_file[_index]; }
		const char *begin() const { return &_file[_index]; }
		const char *end() const { return &_file[_index + _length]; }

		const auto& file() const { return _file; }
		const auto& index() const { return _index; }
		const auto& length() const { return _length; }
		
		Snippet& operator=(const Snippet& other);
		Snippet operator+(const Snippet& other) const;
		bool operator==(const Snippet& other) const;
		const auto& operator[](usize index) const { return _file[_index + index]; }
		friend std::ostream& operator<<(std::ostream& out, const Snippet& snippet);
	};
}

#endif
