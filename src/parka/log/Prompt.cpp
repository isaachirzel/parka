#include "parka/log/Prompt.hpp"
#include "parka/enum/LogEntryType.hpp"
#include "parka/log/Color.hpp"
#include "parka/log/Log.hpp"

namespace parka
{
	const Prompt Prompt::debug("debug", Color::darkBlue);
	const Prompt Prompt::note("note", Color::darkCyan);
	const Prompt Prompt::success("success", Color::brightGreen);
	const Prompt Prompt::warning("warning", Color::darkPurple);
	const Prompt Prompt::error("error", Color::darkRed);
	const Prompt Prompt::solution("solution", Color::darkGreen);
	const Prompt Prompt::fatal("fatal", Color::brightRed);

	Prompt Prompt::from(LogEntryType type)
	{
		switch (type)
		{
			case LogEntryType::Debug:
				return Prompt::debug;

			case LogEntryType::Note:
				return Prompt::note;
					
			case LogEntryType::Success:
				return Prompt::success;

			case LogEntryType::Warning:
				return Prompt::warning;
				
			case LogEntryType::Error:
				return Prompt::error;

			case LogEntryType::Solution:
				return Prompt::solution;

			case LogEntryType::Fatal:
				return Prompt::fatal;

			default:
				break;
		}

		log::fatal("Unable to get Prompt for LogEntryType: $", (int)type);
	}

	std::ostream& operator<<(std::ostream& out, const Prompt& prompt)
	{
		out << prompt._color << prompt._text << Color::reset;

		return out;
	}
}
