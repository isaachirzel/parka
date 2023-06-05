#include "parka/log/Prompt.hpp"
#include "parka/enum/LogEntryType.hpp"
#include "parka/log/Color.hpp"
#include "parka/log/Log.hpp"

namespace parka
{
	const Prompt Prompt::Note("note", Color::Cyan);
	const Prompt Prompt::Success("success", Color::Green);
	const Prompt Prompt::Warning("warning", Color::Purple);
	const Prompt Prompt::Error("error", Color::Red);
	const Prompt Prompt::Fatal("fatal", Color::Red);

	Prompt Prompt::from(LogEntryType type)
	{
		switch (type)
		{
			case LogEntryType::Note:
				return Prompt::Note;
					
			case LogEntryType::Success:
				return Prompt::Success;

			case LogEntryType::Warning:
				return Prompt::Warning;
				
			case LogEntryType::Error:
				return Prompt::Error;

			case LogEntryType::Fatal:
				return Prompt::Fatal;

			default:
				log::fatal("Unable to get Prompt for LogEntryType: $", (int)type);
		}
	}

	std::ostream& operator<<(std::ostream& out, const Prompt& prompt)
	{
		out << prompt._color << prompt._text << Color::Reset;

		return out;
	}
}
