#include "parka/log/Line.hpp"
#include "parka/log/Margin.hpp"

namespace parka
{
	StringView Line::getPreText(const Snippet& snippet)
	{
		const auto& position = snippet.position();
		const char *base = position.file().text().c_str();
		const char *end = position.ptr();
		const char *iter = end;

		while (iter > base)
		{
			if (iter[-1] == '\n')
				break;

			iter -= 1;
		}

		return StringView(iter, end - iter);
	}

	StringView Line::getPostText(const Snippet& snippet)
	{
		const auto& position = snippet.position();
		const char *start = position.ptr() + snippet.length();
		const char *iter = start;

		while (iter[0])
		{
			if (iter[0] == '\n')
				break;

			iter += 1;
		}

		return StringView(start, iter - start);
	}

	std::ostream& operator<<(std::ostream& out, const Line& line)
	{
		auto margin = Margin(line._highlight.position().line());

		out << margin;
		out << Color::Default << line._preText << Color::Reset;
		out << line._highlight;
		out << Color::Default << line._postText << Color::Reset;
		out << '\n';

		return out;
	}
}
