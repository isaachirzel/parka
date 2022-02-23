#include <warbler/source/location.hpp>

namespace warbler::source
{
	Location::Location(usize pos, usize length) :
	_pos(pos),
	_length(length)
	{}

	Location Location::operator+(const Location& other)
	{
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

		return { pos, length };
	}
}