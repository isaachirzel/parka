#include "parka/log/LineSegment.hpp"
#include "parka/fs/FilePosition.hpp"
#include "parka/fs/FileSnippet.hpp"
#include "parka/log/Color.hpp"

namespace parka::log
{
	LineSegment::LineSegment(const fs::FileSnippet& snippet, bool isFocused):
		_snippet(snippet),
		_isFocused(isFocused)
	{}

	Optional<LineSegment> LineSegment::getPreceedingSegment(const fs::FileSnippet& snippet)
	{
		auto position = snippet.position();

		position.seekBeginningOfLine();

		auto diff = snippet.position() - position;

		if (diff == 0)
			return {};

		auto preSnippet = fs::FileSnippet(position, (u32)diff);
		auto preSegment = LineSegment(preSnippet, false);

		return preSegment;
	}

	static Optional<LineSegment> getFollowingSegment(const fs::FileSnippet& snippet)
	{
		auto position = snippet.position();

		position.seekEndOfLine();

		auto diff = position - snippet.position();

		if (diff <= snippet.length())
			return {};

		auto length = diff - snippet.length();
		auto postPosition = fs::FilePosition(position.file(), position.index() + snippet.length(), position.line(), position.column() + snippet.length());
		auto postSnippet = fs::FileSnippet(postPosition, (u32)length);
		auto postSegment = LineSegment(postSnippet, false);

		return postSegment;
	}                   

	Array<LineSegment> LineSegment::getLineSegments(const fs::FileSnippet& fileSnippet)
	{
		// TODO: Optimize this with stack
		// Assume that fileSnippet is contained within one line

		auto preSegment = getPreceedingSegment(fileSnippet);
		auto postSegment = getFollowingSegment(fileSnippet);
		auto segment = LineSegment(fileSnippet, true);
		auto segments = Array<LineSegment>();

		if (preSegment)
			segments.push(*preSegment);

		segments.push(std::move(segment));

		if (postSegment)
			segments.push(*postSegment);

		return segments;
	}

	std::ostream& operator<<(std::ostream& out, const LineSegment& lineSegment)
	{
		if (lineSegment.isFocused())
		{
			out << lineSegment._snippet;
		}
		else
		{
			out << Color::none << lineSegment._snippet << Color::reset;
		}

		return out;
	}
}
