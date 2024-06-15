#include "parka/log/Prompt.hpp"
#include "parka/enum/Severity.hpp"
#include "parka/log/Color.hpp"
#include "parka/log/Log.hpp"

namespace parka
{
	const Prompt Prompt::debug("debug", Color::darkBlue);
	const Prompt Prompt::note("note", Color::darkCyan);
	const Prompt Prompt::success("success", Color::brightGreen);
	const Prompt Prompt::warning("warning", Color::darkPurple);
	const Prompt Prompt::error("error", Color::darkRed);
	const Prompt Prompt::fatal("fatal", Color::brightRed);

	Prompt Prompt::from(Severity type)
	{
		switch (type)
		{
			case Severity::Debug:
				return Prompt::debug;

			case Severity::Note:
				return Prompt::note;
					
			case Severity::Success:
				return Prompt::success;

			case Severity::Warning:
				return Prompt::warning;
				
			case Severity::Error:
				return Prompt::error;

			case Severity::Fatal:
				return Prompt::fatal;
		}

		abort();
	}

	std::ostream& operator<<(std::ostream& out, const Prompt& prompt)
	{
		out << prompt._color << prompt._text << Color::reset;

		return out;
	}
}
