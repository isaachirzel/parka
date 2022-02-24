#ifndef WARBLER_SOURCE_LOCATION_HPP
#define WARBLER_SOURCE_LOCATION_HPP

#include <warbler/util/primitive.hpp>
#include <warbler/source/file.hpp>
#include <warbler/source/text.hpp>

namespace warbler::source
{
	class Location
	{
	private:

		const File& _file;
		usize _pos;
		usize _length;

	public:

		Location(const File& file, usize pos, usize length);

		Snippet get_snippet() const;
		String get_string() const;

		Location operator+(const Location& other) const;

		usize pos() const { return _pos; }
		usize length() const { return _length; }
	};
}

#endif