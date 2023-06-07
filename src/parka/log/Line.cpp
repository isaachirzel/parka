#include "parka/log/Line.hpp"
#include "parka/log/Margin.hpp"

namespace parka
{
	StringView Line::getPreText(const Highlight& highlight)
	{
		const auto& position = highlight.position();
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

	StringView Line::getPostText(const Highlight& highlight)
	{
		const auto& position = highlight.position();
		const char *start = position.ptr() + highlight.length();
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
