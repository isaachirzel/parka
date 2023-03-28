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

#define outputStream stdout

bool isColorEnabled = true;
usize errorCount = 0;
usize warningCount = 0;
usize noteCount = 0;

enum LogLevel
{
	Note,
	Warning,
	Error,
	Success
};

struct Log
{
	const char* prompt;
	const char* color;
	const char* reset;
};

Log createLog(LogLevel level)
{
	const char *prompt = "";
	const char *color = "";
	const char *reset = isColorEnabled
		? COLOR_RESET
		: "";

	switch (level)
	{
		case LogLevel::Note:
			prompt = PROMPT_NOTE;
			
			if (isColorEnabled)
				color = COLOR_CYAN;
			break;
				
		case LogLevel::Warning:
			prompt = PROMPT_WARNING;
			
			if (isColorEnabled)
				color = COLOR_PURPLE;
			break;
			
		case LogLevel::Error:
			prompt = PROMPT_ERROR;

			if (isColorEnabled)
				color = COLOR_RED;
			break;

		case LogLevel::Success:
			prompt = PROMPT_SUCCESS;

			if (isColorEnabled)
				color = COLOR_GREEN;
			break;

		default:
			exitWithErrorFmt("Unable to create Log with LogLevel: %d", level);
	}

	return (Log)
	{
		.prompt = prompt,
		.color = color,
		.reset = reset
	};
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
		sprintf(tempBuffer, "%5zu", lineNumber);
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

String getTokenHighlight(const Token& token, const FilePosition& position, const Log& context)
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
	if (context.color)
	{
		line += context.color;
		underline += context.color;
	}

	line += token.text();
	underline += String(token.length(), '~');

	// Reset
	if (*context.color)
	{
		line += context.reset;
		underline += context.reset;
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

	printf("%s:%u: ", file, line);
}

void _print(const char *file, u32 line, const char *msg)
{
	printFileAndLine(file, line);
	puts(msg);
}

void _printFmt(const char *file, u32 line, const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);

	printFileAndLine(file, line);
	vprintf(fmt, args);
	putchar('\n');

	va_end(args);
}

void printParseError(const Token& token, const char *expected, const char *message)
{
	if (!message)
		message = "";

	printf("Length: %zu\n", token.length());

	if (token.type() == TokenType::EndOfFile)
	{
		printTokenError(token, "Expected %s, found end of file. %s", expected, message);
	}
	else
	{
		auto category = token.category();

		printTokenError(token, "Expected %s, found %s. %s", expected, category.c_str(), message);
	}
}

void printMessage(LogLevel level, const Token *token, const char *format, va_list args)
{
	switch (level)
	{
		case LogLevel::Error:
			errorCount += 1;
			break;

		case LogLevel::Warning:
			warningCount += 1;
			break;

		case LogLevel::Note:
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

	auto log = createLog(level);
	
	std::cout << log.color << log.prompt << log.reset << ": ";
	vprintf(format, args);

	if (token)
	{
		// FIXME: Fix this function to not need position twice
		auto position = token->file().getPosition(token->pos());
		auto highlight = getTokenHighlight(*token, position, log);

		std::cout << '\n' << highlight;
	}

	std::cout << std::endl;
}

void printTokenNote(const Token& token, const char *format, ...)
{
	va_list args;
	va_start(args, format);

	printMessage(LogLevel::Note, &token, format, args);

	va_end(args);
}

void printTokenWarning(const Token& token, const char *format, ...)
{
	va_list args;
	va_start(args, format);

	printMessage(LogLevel::Warning, &token, format, args);

	va_end(args);
}

void printTokenError(const Token& token, const char *format, ...)
{
	va_list args;
	va_start(args, format);

	printMessage(LogLevel::Error, &token, format, args);

	va_end(args);
}

void printNote(const char *format, ...)
{
	va_list args;
	va_start(args, format);

	printMessage(LogLevel::Note, NULL, format, args);

	va_end(args);
}

void printWarning(const char *format, ...)
{
	va_list args;
	va_start(args, format);

	printMessage(LogLevel::Warning, NULL, format, args);

	va_end(args);
}

void printError(const char *format, ...)
{
	va_list args;
	va_start(args, format);

	printMessage(LogLevel::Error, NULL, format, args);
	
	va_end(args);
}

void printSuccess(const char *format, ...)
{
	va_list args;
	va_start(args, format);

	printMessage(LogLevel::Success, NULL, format, args);
	
	va_end(args);
}

[[ noreturn ]]
void _exitWithError(const char *file, usize line, const char *format, ...)
{
	va_list args;

	va_start(args, format);

	printFileAndLine(file, line);
	printf(COLOR_RED "fatal" COLOR_RESET ": ");
	vprintf(format, args);
	putchar('\n');

	va_end(args);

	exit(1);
}

[[ noreturn ]]
void _exitNotImplemented(const char *file, usize line, const char *func)
{
	printFileAndLine(file, line);
	printf(COLOR_RED "fatal" COLOR_RESET ": %s is not implemented.\n", func);
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
