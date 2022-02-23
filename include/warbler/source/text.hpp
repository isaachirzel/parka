#ifndef WARBLER_SOURCE_TEXT_HPP
#define WARBLER_SOURCE_TEXT_HPP

#include <warbler/util/string.hpp>
#include <warbler/source/location.hpp>

namespace warbler::source
{
	class Text
	{
	private:

		String _filename;
		String _data;
		Location _location;
		usize _line;
		usize _col;

	public:

		Text(String&& filename, String&& data, const Location& location, usize line, usize col);

		const String& filename() const { return _filename; }
		const String& data() const { return _data; }
		const Location& location() const { return _location; }
		usize line() const { return _line; }
		usize col() const { return _col; }
	};
}

#endif
