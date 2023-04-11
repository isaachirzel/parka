#include "parka/util/Prompt.hpp"
#include "parka/util/Print.hpp"

#define COLOR_RED		"\033[91m"
#define COLOR_YELLOW	"\033[93m"
#define COLOR_BLUE		"\033[94m"
#define COLOR_PURPLE	"\033[95m"
#define COLOR_CYAN		"\033[96m"
#define COLOR_GREEN		"\033[32m"
#define COLOR_RESET		"\033[0m"

#define PROMPT_NOTE		"note"
#define PROMPT_WARNING	"warning"
#define PROMPT_ERROR	"error"
#define PROMPT_FATAL	"fatal"
#define PROMPT_SUCCESS	"success"

namespace parka
{
	Prompt::Prompt(PromptType type)
	{
		switch (type)
		{
			case PromptType::Note:
				_text = PROMPT_NOTE;
				
				if (isColorPrintingEnabled())
				{
					_color = COLOR_CYAN;
					_reset = COLOR_RESET;
				}
				break;
					
			case PromptType::Warning:
				_text = PROMPT_WARNING;
				
				if (isColorPrintingEnabled())
				{
					_color = COLOR_PURPLE;
					_reset = COLOR_RESET;
				}
				break;
				
			case PromptType::Error:
				_text = PROMPT_ERROR;

				if (isColorPrintingEnabled())
				{
					_color = COLOR_RED;
					_reset = COLOR_RESET;
				}
				break;

			case PromptType::Fatal:
				_text = PROMPT_FATAL;

				if (isColorPrintingEnabled())
				{
					_color = COLOR_RED;
					_reset = COLOR_RESET;
				}
				break;

			case PromptType::Success:
				_text = PROMPT_SUCCESS;

				if (isColorPrintingEnabled())
				{
					_color = COLOR_GREEN;
					_reset = COLOR_RESET;
				}
				break;

			default:
				exitWithError("Unable to create Log with PromptType: $", type);
		}
	}

	std::ostream& operator<<(std::ostream& out, const Prompt& prompt)
	{
		out << prompt._color << prompt._text << prompt._reset << ':';

		return out;
	}
}
