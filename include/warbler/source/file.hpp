#ifndef WARBLER_SOURCE_FILE_HPP
#define WARBLER_SOURCE_FILE_HPP

#include <warbler/source/text.hpp>
#include <warbler/util/array.hpp>
#include <warbler/util/result.hpp>

#include <cassert>

namespace warbler::source
{
	class File
	{
	private:

		String _filename;
		String _src;
		Array<usize> _line_lengths;

		File(String&& filename, String&& src, Array<usize>&& line_lengths);

	public:

		static Result<File> read(const String& filepath);
		static File from(const char *text);

		Text get_text(usize pos, usize length);
		String get_string(const Location& location) const;

		char operator[](usize i) const { assert(i < _src.size()); return _src[i]; }

		const String& filename() const { return _filename; }
		const String& src() const { return _src; }
		const Array<usize>& line_lengths() const { return _line_lengths; }
	};
}

#endif
