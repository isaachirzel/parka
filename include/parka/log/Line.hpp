#ifndef PARK_LOG_LINE_HPP
#define PARK_LOG_LINE_HPP

#include "parka/fs/FileSnippet.hpp"
#include "parka/log/LineSegment.hpp"
#include "parka/util/Array.hpp"

#include <ostream>

namespace parka::log
{
	class Line
	{
		// TODO: This could be optimized

		Array<LineSegment> _segments;

	public:

		Line(Array<LineSegment>&& segments);
		Line(Line&&) = default;
		Line(const Line&) = delete;

		static Array<Line> getLines(const fs::FileSnippet& snippet);

		friend std::ostream& operator<<(std::ostream& out, const Line& underline);
	};
}

#endif
