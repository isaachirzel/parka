#include "parka/log/LogEntry.hpp"
#include "parka/enum/LogEntryType.hpp"
#include "parka/log/Color.hpp"
#include "parka/log/Line.hpp"
#include "parka/log/Log.hpp"
#include "parka/log/Margin.hpp"
#include "parka/log/Prompt.hpp"
#include "parka/log/Underline.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	Color LogEntry::getColor(LogEntryType type)
	{
		switch (type)
		{
			case LogEntryType::Note:
				return Color::Cyan;

			case LogEntryType::Success:
				return Color::Green;

			case LogEntryType::Warning:
				return Color::Purple;

			case LogEntryType::Error:
				return Color::Red;

			case LogEntryType::Fatal:
				return Color::Red;

			default:
				break;
		}

		Log::fatal("Unable to get Color for LogEntryType %d", (int)type);
	}

	std::ostream& operator<<(std::ostream& out, const LogEntry& entry)
	{
		auto prompt = Prompt::from(entry._type);

		out << entry._color;

		if (entry._highlight)
			out << entry._highlight->position() << '\n';

		out << prompt << Color::Default << ": " << entry._message << Color::Reset << '\n';

		if (entry._highlight)
		{
			// TODO: Different color for type
			auto line = Line(*entry._highlight);
			auto underline = Underline(*entry._highlight);
			out << Margin() << '\n';
			out << line;
			out << underline;
		}

		out << Color::Reset << '\n';

		return out;
	}
}