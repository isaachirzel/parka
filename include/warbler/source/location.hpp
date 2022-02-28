#ifndef WARBLER_SOURCE_LOCATION_HPP
#define WARBLER_SOURCE_LOCATION_HPP

#include <warbler/source/snippet.hpp>

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
		String text() const;

		usize pos() const { return _pos; }
		usize length() const { return _length; }
	};
}

#endif