#include "parka/log/Highlight.hpp"

#include <sstream>

namespace parka
{
	usize getStartOfLine(const char *text, usize pos)
	{
		while (pos > 1)
		{
			if (text[pos - 1] == '\n')
				return pos;

			--pos;
		}

		return 0;
	}

	const char *getEndOfLine(const char *iter)
	{
		while (*iter)
		{
			if (*iter == '\n')
				break;
			iter += 1;
		}

		return iter;
	}

	usize getNumberWidth(usize number)
	{
		// TODO: get line count to make sure it doesn't overflow
		usize out = 1;
		
		while (number > 9)
		{
			out += 1;
			number /= 10;
		}

		return out;
	}

	String toInvisible(const char *start, usize n)
	{
		auto text = String(n, ' ');

		for (usize i = 0; i < n; ++i)
		{
			if (start[i] == '\t')
				text[i] = '\t';
		}

		return text;
	}

	String toMargin(usize lineNumber, usize numberWidth)
	{
		const char *divider = " | ";

		if (lineNumber == 0)
			return String(numberWidth, ' ') + divider;

		auto text = std::to_string(lineNumber);

		if (text.length() < numberWidth)
			text.insert(0, String(numberWidth - text.length(), ' '));

		return text + " | ";
	}

	std::ostream& operator<<(std::ostream& out, const Highlight& highlight)
	{
		const auto* ptr = highlight._position.ptr();

		out.write(ptr, highlight._length);
		// // TODO: Handle multiline tokens
		// const auto& position = highlight._position;
		// const auto& file = position.file();
		// auto lineCount = file.lineCount();
		// auto numberWidth = getNumberWidth(lineCount);
		// auto text = std::ostringstream();
		// auto line = std::ostringstream();
		// auto underline = std::ostringstream();
		// auto pos = getStartOfLine(file.text().c_str(), position.index());

		// line << toMargin(highlight.position().line(), numberWidth);
		// underline << toMargin(0, numberWidth);

		// const char *start = file.text().c_str() + pos;
		// usize startLength = position.index() - pos;

		// // Start of Line
		// line << String(start, startLength);
		// underline << toInvisible(start, startLength);

		// // Color

		// // line << highlight.color();
		// // underline << highlight.color();

		// line.write(file.text().c_str() + position.index(), highlight.length());

		// for (usize i = 0; i < highlight.length(); ++i)
		// 	underline.put('~');

		// // Reset
		// line << Color::Reset;
		// underline << Color::Reset;

		// const char *endOfLine = getEndOfLine(highlight.end());

		// line.write(highlight.end(), endOfLine - highlight.end());
		// line << '\n';
		// underline << '\n';

		// out << line.rdbuf();
		// out << underline.rdbuf();
		// out << '\n';

		return out;
	}
}
