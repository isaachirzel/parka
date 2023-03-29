#ifndef PARKA_UTIL_PROMPT_HPP
#define PARKA_UTIL_PROMPT_HPP

#include <ostream>

enum class PromptType
{
	Note,
	Warning,
	Error,
	Fatal,
	Success
};

class Prompt
{
	const char* _text = "";
	const char* _color = "";
	const char* _reset = "";

public:

	Prompt(PromptType type);
	
	friend std::ostream& operator<<(std::ostream& out, const Prompt& prompt);

	const auto *text() const { return _text; }
	const auto *color() const { return _color; }
	const auto *reset() const { return _reset; }
};

#endif
