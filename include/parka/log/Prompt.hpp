#ifndef PARKA_UTIL_PROMPT_HPP
#define PARKA_UTIL_PROMPT_HPP

#include "parka/enum/Severity.hpp"
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

		static const Prompt debug;
		static const Prompt note;
		static const Prompt success;
		static const Prompt warning;
		static const Prompt error;
		static const Prompt solution;
		static const Prompt fatal;

	public:

		Prompt(Prompt&&) = default;
		Prompt(const Prompt&) = default;

		static Prompt from(Severity type);
		
		const auto *text() const { return _text; }
		const auto& color() const { return _color; }

		friend std::ostream& operator<<(std::ostream& out, const Prompt& prompt);
	};
}

#endif
