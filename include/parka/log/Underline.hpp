#ifndef PARKA_LOG_HIGHLIGHT_HPP
#define PARKA_LOG_HIGHLIGHT_HPP

#include "parka/log/Highlight.hpp"
#include "parka/log/Line.hpp"

#include <ostream>

namespace parka
{
	class Underline
	{
		StringView _preText;
		usize _length;

	public:

		Underline(const Line& line) :
		_preText(line.preText()),
		_length(line.highlight().length())
		{}
		
		friend std::ostream& operator<<(std::ostream& out, const Underline& underline);
	};
}

#endif
