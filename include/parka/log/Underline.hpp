#ifndef PARKA_LOG_HIGHLIGHT_HPP
#define PARKA_LOG_HIGHLIGHT_HPP

#include "parka/file/Snippet.hpp"
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
		_length(line.snippet().length())
		{}
		
		friend std::ostream& operator<<(std::ostream& out, const Underline& underline);
	};
}

#endif
