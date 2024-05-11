#ifndef PARKA_UTIL_PROMPT_HPP
#define PARKA_UTIL_PROMPT_HPP

#include "parka/enum/LogEntryType.hpp"
#include "parka/log/Color.hpp"
#include <ostream>

namespace parka
{
	class Prompt
	{
		const char* _text;
		Color _color;

		Prompt(const char *text, const Color& color):
			_text(text),
			_color(color)
		{}

	public:

		static const Prompt Debug;
		static const Prompt Note;
		static const Prompt Success;
		static const Prompt Warning;
		static const Prompt Error;
		static const Prompt Fatal;

	public:

		Prompt(Prompt&&) = default;
		Prompt(const Prompt&) = default;

		static Prompt from(LogEntryType type);
		
		const auto *text() const { return _text; }
		const auto& color() const { return _color; }

		friend std::ostream& operator<<(std::ostream& out, const Prompt& prompt);
	};
}

#endif
