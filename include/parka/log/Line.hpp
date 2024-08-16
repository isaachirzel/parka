#ifndef PARK_LOG_LINE_HPP
#define PARK_LOG_LINE_HPP

#include "parka/fs/FileSnippet.hpp"
#include "parka/util/StringView.hpp"

#include <ostream>

namespace parka::log
{
	class Line
	{
		fs::FileSnippet _snippet;
		StringView _preText;
		StringView _postText;

		static StringView getPreText(const fs::FileSnippet& snippet);
		static StringView getPostText(const fs::FileSnippet& snippet);

	public:

		Line(const fs::FileSnippet& snippet):
		_snippet(snippet),
		_preText(getPreText(snippet)),
		_postText(getPostText(snippet))
		{}

		const auto& snippet() const { return _snippet; }
		const auto& preText() const { return _preText; }
		const auto& postText() const { return _preText; }

		friend std::ostream& operator<<(std::ostream& out, const Line& underline);
	};
}

#endif
