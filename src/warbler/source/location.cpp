#include <warbler/source/location.hpp>

#include <cassert>

namespace warbler::source
{
	Location::Location(const File& file, usize pos, usize length) :
	_file(file),
	_pos(pos),
	_length(length)
	{}
}