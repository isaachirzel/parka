#include "parka/log/LogEntry.hpp"
#include "parka/log/Color.hpp"
#include "parka/log/Line.hpp"
#include "parka/log/Margin.hpp"
#include "parka/log/Prompt.hpp"
#include "parka/log/Underline.hpp"

namespace parka
{
	std::ostream& operator<<(std::ostream& out, const LogEntry& entry)
	{
		auto prompt = Prompt::from(entry._type);

		out << prompt.color(); // This sets the highlight color?

		if (entry._snippet)
		{
			const auto& position = entry._snippet->position();

			out << Color::darkYellow;
			out << position.file().path() << ":" << position.line() << ":" << position.column();
			out << Color::reset;
			out << "\n";
		}

		out << prompt << Color::none << ": " << entry._message << Color::reset << '\n';

		if (entry._snippet)
		{
			// TODO: Different color for type
			auto line = Line(*entry._snippet);
			auto underline = Underline(*entry._snippet);
			out << Margin() << '\n';
			out << line;
			out << underline;
		}

		out << Color::reset << '\n';

		return out;
	}
}