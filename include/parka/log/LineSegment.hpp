#include "parka/fs/FileSnippet.hpp"
#include "parka/util/Array.hpp"
#include "parka/util/Optional.hpp"

namespace parka::log
{
	class LineSegment
	{
		fs::FileSnippet _snippet;
		bool _isFocused;

	public:
		
		LineSegment(const fs::FileSnippet& snippet, bool isFocused);
		LineSegment(LineSegment&&) = default;
		LineSegment(const LineSegment&) = default;
		
		static Optional<LineSegment> getPreceedingSegment(const fs::FileSnippet& snippet);
		static Array<LineSegment> getLineSegments(const fs::FileSnippet& fileSnippet);

		const auto& snippet() const { return _snippet; }
		const auto& isFocused() const { return _isFocused; }

		friend std::ostream& operator<<(std::ostream& out, const LineSegment& lineSegment);
	};
}
