#include "parka/log/Indent.hpp"
#include <ios>

namespace parka::log
{
	const int Indent::xIndex = std::ios_base::xalloc();


	Indent::Indent(std::ostream& stream):
	_amount(stream.iword(Indent::xIndex))
	{
		_amount += 1;
	}

	Indent::~Indent()
	{
		_amount -= 1;
	}

	std::ostream& operator<<(std::ostream& out, const Indent& indent)
	{
		// TODO: Optimize
		for (isize i = 0; i < indent._amount - 1; ++i)
			out.put('\t');

		return out;
	}
}
