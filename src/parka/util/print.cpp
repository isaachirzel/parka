#include "parka/util/path.hpp"
#include "parka/util/print.hpp"

// standard headers
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <limits.h>
#include "parka/util/primitives.hpp"
#include "parka/util/string.hpp"



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

typedef enum LogLevel
{
	LOG_NOTE,
	LOG_WARNING,
	LOG_ERROR,
	LOG_SUCCESS
} LogLevel;

typedef struct Log
{
	const char* prompt;
	const char* color;
	const char* reset;
} Log;

Log createLog(LogLevel level)
{
	const char *prompt = "";
	const char *color = "";
	const char *reset = isColorEnabled
		? COLOR_RESET
		: "";

	switch (level)
	{
		case LOG_NOTE:
			prompt = PROMPT_NOTE;
			
			if (isColorEnabled)
				color = COLOR_CYAN;
			break;
				
		case LOG_WARNING:
			prompt = PROMPT_WARNING;
			
			if (isColorEnabled)
				color = COLOR_PURPLE;
			break;
			
		case LOG_ERROR:
			prompt = PROMPT_ERROR;

			if (isColorEnabled)
				color = COLOR_RED;
			break;

		case LOG_SUCCESS:
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

void sbPushMargin(StringBuilder *builder, usize line)
{
	const usize numberWidth = 5;

	char tempBuffer[numberWidth + 4];

	if (line > 0)
	{
		sprintf(tempBuffer, "%5zu", line);
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

	sbPushString(builder, tempBuffer);
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

char *getTokenHighlight(const Token& token, const FilePosition *position, const Log *context)
{
	// TODO: Handle multiline tokens
	// TODO: Handle tabs
	const File *file = token.file();

	StringBuilder highlight = sbCreate(256);
	StringBuilder line = sbCreate(128);
	StringBuilder underline = sbCreate(128);

	usize pos = getStartOfLine(file->src, token.pos());

	sbPushMargin(&line, position->line);
	sbPushMargin(&underline, 0);

	const char *start = file->src + pos;
	usize startLength = token.pos() - pos;

	// Start of Line
	sbPushStringN(&line, start, startLength);
	sbPushStringInvisibleN(&underline, start, startLength);

	// Color
	if (*context->color)
	{
		sbPushString(&line, context->color);
		sbPushString(&underline, context->color);
	}

	// Token
	const char *text  = file->src + token.pos();

	sbPushStringN(&line, text, token.length());
	sbPushCharN(&underline, '~', token.length());

	// Reset
	if (*context->color)
	{
		sbPushString(&line, context->reset);
		sbPushString(&underline, context->reset);
	}

	const char *end = text + token.length();
	const char *endPos = sbPushLine(&line, end);

	sbPushStringInvisibleN(&underline, end, endPos - end);

	sbPushChar(&line, '\n');
	sbPushChar(&underline, '\n');

	sbPushString(&highlight, line.data);
	sbPushString(&highlight, underline.data);
	sbPushChar(&highlight, '\n');

	return highlight.data;
}

void printFileAndLine(const char *file, u32 line)
{
	// TODO: Make OS agnostic
	usize index = stringFindOccurrence(file, "/src/");

	if (index != PATH_MAX)
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
		const char *category = tokenCategory(token);

		printTokenError(token, "Expected %s, found %s. %s", expected, category, message);
	}
}

void printMessage(LogLevel level, const Token& token, const char *format, va_list args)
{
	FilePosition position;

	switch (level)
	{
		case LOG_ERROR:
			errorCount += 1;
			break;

		case LOG_WARNING:
			warningCount += 1;
			break;

		case LOG_NOTE:
			noteCount += 1;
			break;

		default:
			break;
	}

	if (token)
	{
		position = fileGetPosition(token.file(), token.pos());

		printf("%s:%zu:%zu: ", token.file()->path, position.line, position.col);
	}

	Log log = createLog(level);
	
	printf("%s%s%s: ", log.color, log.prompt, log.reset);
	vprintf(format, args);
	putchar('\n');

	if (token)
	{
		char* highlight = getTokenHighlight(token, &position, &log);

		puts(highlight);
		deallocate(highlight);
	}
}

void printTokenNote(const Token& token, const char *format, ...)
{
	va_list args;
	va_start(args, format);

	printMessage(LOG_NOTE, token, format, args);

	va_end(args);
}

void printTokenWarning(const Token& token, const char *format, ...)
{
	va_list args;
	va_start(args, format);

	printMessage(LOG_WARNING, token, format, args);

	va_end(args);
}

void printTokenError(const Token& token, const char *format, ...)
{
	va_list args;
	va_start(args, format);

	printMessage(LOG_ERROR, token, format, args);

	va_end(args);
}

void printNote(const char *format, ...)
{
	va_list args;
	va_start(args, format);

	printMessage(LOG_NOTE, NULL, format, args);

	va_end(args);
}

void printWarning(const char *format, ...)
{
	va_list args;
	va_start(args, format);

	printMessage(LOG_WARNING, NULL, format, args);

	va_end(args);
}

void printError(const char *format, ...)
{
	va_list args;
	va_start(args, format);

	printMessage(LOG_ERROR, NULL, format, args);
	
	va_end(args);
}

void printSuccess(const char *format, ...)
{
	va_list args;
	va_start(args, format);

	printMessage(LOG_SUCCESS, NULL, format, args);
	
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
