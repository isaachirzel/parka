#ifndef PARK_LOG_LINE_HPP
#define PARK_LOG_LINE_HPP

#include "parka/log/Highlight.hpp"
#include "parka/util/StringView.hpp"

#include <ostream>

namespace parka
{
	class Line
	{
		Highlight _highlight;
		StringView _preText;
		StringView _postText;

		static StringView getPreText(const Highlight& highlight);
		static StringView getPostText(const Highlight& highlight);

	public:

		Line(const Highlight& highlight) :
		_highlight(highlight),
		_preText(getPreText(highlight)),
		_postText(getPostText(highlight))
		{}

		const auto& highlight() const { return _highlight; }
		const auto& preText() const { return _preText; }
		const auto& postText() const { return _preText; }

		friend std::ostream& operator<<(std::ostream& out, const Line& underline);
	};
}

#endif
