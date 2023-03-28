#include "parka/util/path.hpp"
#include "parka/util/print.hpp"
#include "parka/util/primitives.hpp"
#include "parka/util/string.hpp"

#include <iostream> 
#include <cstdarg>
#include <cstring>

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
#define PROMPT_SUCCESS	"success"

bool isColorEnabled = true;
usize errorCount = 0;
usize warningCount = 0;
usize noteCount = 0;

Prompt::Prompt(PromptType type)
{
	switch (type)
	{
		case PromptType::Note:
			_text = PROMPT_NOTE;
			
			if (isColorEnabled)
			{
				_color = COLOR_CYAN;
				_reset = COLOR_RESET;
			}
			break;
				
		case PromptType::Warning:
			_text = PROMPT_WARNING;
			
			if (isColorEnabled)
			{
				_color = COLOR_PURPLE;
				_reset = COLOR_RESET;
			}
			break;
			
		case PromptType::Error:
			_text = PROMPT_ERROR;

			if (isColorEnabled)
			{
				_color = COLOR_RED;
				_reset = COLOR_RESET;
			}
			break;

		case PromptType::Success:
			_text = PROMPT_SUCCESS;

			if (isColorEnabled)
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
	out << prompt._color << prompt._text << prompt._reset << ": ";

	return out;
}

void enableColorPrinting(bool enabled)
{
	isColorEnabled = enabled;
}

usize getNumberWidth(usize number)
{
	usize out = 1;
	
	while (number > 9)
	{
		out += 1;
		number /= 10;
	}

	return out;
}

String toMargin(usize lineNumber)
{
	const usize numberWidth = 5;

	char tempBuffer[numberWidth + 4];

	if (lineNumber > 0)
	{
		sprintf(tempBuffer, "$5zu", lineNumber);
	}
	else
	{
		for (usize i = 0; i < numberWidth; ++i)
			tempBuffer[i] = ' ';
	}

	tempBuffer[numberWidth] = ' ';
	tempBuffer[numberWidth + 1] = '|';
	tempBuffer[numberWidth + 2] = ' ';
	tempBuffer[numberWidth + 3] = '\0';

	return tempBuffer;
}

String toInvisible(const char *start, usize n)
{
	auto text = String(n, ' ');

    for (usize i = 0; i < n; ++i)
    {
		if (start[i] == '\t')
			text[i] = '\t';
    }

	return text;
}

usize getStartOfLine(const char *text, usize pos)
{
	while (pos > 1)
	{
		if (text[pos - 1] == '\n')
			return pos;

		--pos;
	}

	return 0;
}

String getLine(const char *str)
{
	const char *end;

	for (end = str; *end && *end != '\n'; ++end);	

	auto text = String(str, end - str);
	
	return text;
}

usize findOccurrence(const char *text, const char *token)
{
    assert(text != NULL);
    assert(token != NULL);

    char starter = token[0];
    usize length = strlen(token);

    for (const char *iter = text; *iter; ++iter)
    {
        if (*iter != starter)
            continue;

        if (!strncmp(iter, token, length))
            return iter - text;
    }

    return SIZE_MAX;
}

String getTokenHighlight(const Token& token, const FilePosition& position, const Prompt& context)
{
	// TODO: Handle multiline tokens
	const File& file = token.file();

	auto highlight = String();
	auto line = String();
	auto underline = String();
	auto pos = getStartOfLine(file.text().c_str(), token.pos());

	line += toMargin(position.line());
	underline += toMargin(0);

	const char *start = file.text().c_str() + pos;
	usize startLength = token.pos() - pos;

	// Start of Line
	line += String(start, startLength);
	underline += toInvisible(start, startLength);

	// Color
	if (context.color())
	{
		line += context.color();
		underline += context.color();
	}

	line += token.text();
	underline += String(token.length(), '~');

	// Reset
	if (*context.color())
	{
		line += context.reset();
		underline += context.reset();
	}

	const char *end = &file[token.pos() + token.length()];
	line += getLine(end);
	line += '\n';
	underline += '\n';
	highlight += line;
	highlight += underline;
	highlight += '\n';

	return highlight;
}

void printFileAndLine(const char *file, u32 line)
{
	// TODO: Make OS agnostic
	usize index = findOccurrence(file, "/src/");

	if (index != SIZE_MAX)
		file += (index + 5);

	printf("$:$u: ", file, line);
}

void _print(const char * const fmt)
{
	// TODO: Escape $ symbol
	for (const char * iter = fmt; *iter; ++iter)
	{
		if (*iter == '$')
		{
			std::cout << "Not enough arguments to print." << std::endl;
			exit(1);
		}
	}

	std::cout << fmt << std::endl;
}

void printParseError(const Token& token, const char *expected, const char *message)
{
	if (!message)
		message = "";

	printf("Length: $\n", token.length());

	if (token.type() == TokenType::EndOfFile)
	{
		printTokenError(token, "Expected $, found end of file. $", expected, message);
	}
	else
	{
		auto category = token.category();

		printTokenError(token, "Expected $, found $. $", expected, category.c_str(), message);
	}
}

void printMessage(PromptType type, const Token *token, const char *format, va_list args)
{
	switch (type)
	{
		case PromptType::Error:
			errorCount += 1;
			break;

		case PromptType::Warning:
			warningCount += 1;
			break;

		case PromptType::Note:
			noteCount += 1;
			break;

		default:
			break;
	}

	if (token)
	{
		auto position = token->file().getPosition(token->pos());

		std::cout << token->file().path() << ':' << position.line() << ':' << position.col() << ": ";
	}

	auto prompt = Prompt(type);
	
	std::cout << prompt;

	vprintf(format, args);

	if (token)
	{
		// FIXME: Fix this function to not need position twice
		auto position = token->file().getPosition(token->pos());
		auto highlight = getTokenHighlight(*token, position, prompt);

		std::cout << '\n' << highlight;
	}

	std::cout << std::endl;
}

void printTokenNote(const Token& token, const char *format, ...)
{
	va_list args;
	va_start(args, format);

	printMessage(PromptType::Note, &token, format, args);

	va_end(args);
}

void printTokenWarning(const Token& token, const char *format, ...)
{
	va_list args;
	va_start(args, format);

	printMessage(PromptType::Warning, &token, format, args);

	va_end(args);
}

void printTokenError(const Token& token, const char *format, ...)
{
	va_list args;
	va_start(args, format);

	printMessage(PromptType::Error, &token, format, args);

	va_end(args);
}

void printNote(const char *format, ...)
{
	va_list args;
	va_start(args, format);

	printMessage(PromptType::Note, NULL, format, args);

	va_end(args);
}

void printWarning(const char *format, ...)
{
	va_list args;
	va_start(args, format);

	printMessage(PromptType::Warning, NULL, format, args);

	va_end(args);
}

void printError(const char *format, ...)
{
	va_list args;
	va_start(args, format);

	printMessage(PromptType::Error, NULL, format, args);
	
	va_end(args);
}

void printSuccess(const char *format, ...)
{
	va_list args;
	va_start(args, format);

	printMessage(PromptType::Success, NULL, format, args);
	
	va_end(args);
}

[[ noreturn ]]
void exitNotImplemented(SourceLocation&& location)
{
	printFileAndLine(location.file(), location.line());
	printf(COLOR_RED "fatal" COLOR_RESET ": $ is not implemented.\n", location.function());
	exit(1);
}

usize getNoteCount(void)
{
	return noteCount;
}

usize getWarningCount(void)
{
	return warningCount;
}

usize getErrorCount(void)
{
	return errorCount;
}
