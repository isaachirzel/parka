#ifndef PARK_LOG_LINE_HPP
#define PARK_LOG_LINE_HPP

#include "parka/file/Snippet.hpp"
#include "parka/util/StringView.hpp"

#include <ostream>

namespace parka
{
	class Line
	{
		Snippet _highlight;
		StringView _preText;
		StringView _postText;

		static StringView getPreText(const Snippet& snippet);
		static StringView getPostText(const Snippet& snippet);

	public:

		Line(const Snippet& snippet) :
		_highlight(snippet),
		_preText(getPreText(snippet)),
		_postText(getPostText(snippet))
		{}

		const auto& snippet() const { return _highlight; }
		const auto& preText() const { return _preText; }
		const auto& postText() const { return _preText; }

		friend std::ostream& operator<<(std::ostream& out, const Line& underline);
	};
}

#endif
