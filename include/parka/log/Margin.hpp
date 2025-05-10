#ifndef PARKA_LOG_MARGIN_HPP
#define PARKA_LOG_MARGIN_HPP

#include "parka/util/Common.hpp"

#include <ostream>

namespace parka::log
{
	class Margin
	{
		usize _lineNumber;
		
		static const int xIndex;

	public:

		Margin(usize lineNumber = 0);

		friend std::ostream& operator<<(std::ostream& out, const Margin& margin);
	};
}

#endif
