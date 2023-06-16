#include "parka/log/LogEntry.hpp"
#include "parka/enum/LogEntryType.hpp"
#include "parka/log/Color.hpp"
#include "parka/log/Line.hpp"
#include "parka/log/Log.hpp"
#include "parka/log/Margin.hpp"
#include "parka/log/Prompt.hpp"
#include "parka/log/Underline.hpp"

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

		log::fatal("Unable to get Color for LogEntryType %d", (int)type);
	}

	std::ostream& operator<<(std::ostream& out, const LogEntry& entry)
	{
		auto prompt = Prompt::from(entry._type);

		out << entry._color;

		if (entry._snippet)
		{
			const auto& snippet = *entry._snippet;

			out << Color::Yellow;
			out << snippet.file().path() << ":" << snippet.line() << ":" << snippet.col();
			out << Color::Reset;
			out << "\n";
		}

		out << prompt << Color::Default << ": " << entry._message << Color::Reset << '\n';

		if (entry._snippet)
		{
			// TODO: Different color for type
			auto line = Line(*entry._snippet);
			auto underline = Underline(*entry._snippet);
			out << Margin() << '\n';
			out << line;
			out << underline;
		}

		out << Color::Reset << '\n';

		return out;
	}
}