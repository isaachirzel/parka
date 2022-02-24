#include <warbler/source/location.hpp>

#include <cassert>

namespace warbler::source
{
	Location::Location(const File& file, usize pos, usize length) :
	_file(file),
	_pos(pos),
	_length(length)
	{}

	Location Location::operator+(const Location& other) const
	{
		assert(&_file == &other._file);

		const Location *min;
		const Location *max;

		if (_pos <= other._pos)
		{
			min = this;
			max = &other;
		}
		else
		{
			min = &other;
			max = this;
		}

		auto pos = min->_pos;
		auto length = (max->_pos + max->_length) - min->_pos;

		return { _file, pos, length };
	}
}