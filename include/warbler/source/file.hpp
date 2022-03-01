#ifndef WARBLER_SOURCE_FILE_HPP
#define WARBLER_SOURCE_FILE_HPP

#include <warbler/util/array.hpp>
#include <warbler/util/result.hpp>
#include <warbler/util/primitive.hpp>
#include <warbler/util/string.hpp>

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

		usize get_line(usize pos) const;
		usize get_col(usize pos) const;

		String get_text(usize pos, usize length) const;
		char operator[](usize i) const { assert(i < _src.size()); return _src[i]; }

		const String& filename() const { return _filename; }
		const String& src() const { return _src; }
	};
}

#endif
