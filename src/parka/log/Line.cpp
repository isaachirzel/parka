#include "parka/log/Line.hpp"
#include "parka/fs/FileSnippet.hpp"
#include "parka/log/Margin.hpp"

namespace parka::log
{
	Line::Line(Array<LineSegment>&& segments):
		_segments(std::move(segments))
	{}

	Array<Line> Line::getLines(const fs::FileSnippet& snippet)
	{
		// TODO: Implement this	

		auto preSegment = LineSegment::getPreceedingSegment(snippet);

		for (usize i = 0; i < snippet.length(); ++i)
		{

		}

		return {};
	}

	std::ostream& operator<<(std::ostream& out, const Line& line)
	{
		if (line._segments.length() == 0)
			return out;

		const auto& first = line._segments[0];
		const auto lineNumber = first.snippet().position().line();
		const auto margin = Margin(lineNumber);

		out << margin;

		for (const auto& segment : line._segments)
		{
			out << segment;
		}

		out << '\n';

		return out;
	}
}
