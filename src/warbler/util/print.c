#include <warbler/util/print.h>

// standard headers
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <warbler/util/primitives.h>
#include <warbler/util/string.h>
#include <warbler/util/memory.h>

#define COLOR_RED		"\033[91m"
#define COLOR_YELLOW	"\033[93m"
#define COLOR_BLUE		"\033[94m"
#define COLOR_PURPLE	"\033[95m"
#define COLOR_CYAN		"\033[96m"
#define COLOR_RESET		"\033[0m"

#define PROMPT_NOTE		"note"
#define PROMPT_WARNING	"warning"
#define PROMPT_ERROR	"error"

#define outputStream stdout

static bool isColorEnabled = true;

typedef enum LogLevel
{
	LOG_NOTE,
	LOG_WARNING,
	LOG_ERROR
} LogLevel;

typedef struct LogContext
{
	const char* prompt;
	const char* color;
	const char* reset;
} LogContext;

static LogContext createLogContext(LogLevel level)
{
	const char *prompt = "";
	const char *color = "";
	const char *reset = "";

	switch (level)
	{
		case LOG_NOTE:
			prompt = PROMPT_NOTE;
			
			if (isColorEnabled)
			{
				color = COLOR_CYAN;
				reset = COLOR_RESET;
			}
			break;
				
		case LOG_WARNING:
			prompt = PROMPT_WARNING;
			
			if (isColorEnabled)
			{
				color = COLOR_PURPLE;
				reset = COLOR_RESET;
			}
			break;
			
		case LOG_ERROR:
			prompt = PROMPT_ERROR;

			if (isColorEnabled)
			{
				color = COLOR_RED;
				reset = COLOR_RESET;
			}
			break;

		default:
			exitWithError("Invalid LogLevel: %d", level);
	}

	return (LogContext)
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

// static const char *getShortenedFile(const char *file)
// {

// 	for (const char *pos = file; *pos; pos += 1)
// 	{
// 		if (!strncmp(pos, "warbler/", 8))
// 			return pos + 8;
// 	}

// 	return file;
// }

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

void stringPushMargin(String *string, usize line)
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

	stringPush(string, tempBuffer);
}

char *getSnippetHighlight(const Snippet *snippet, const LogContext *context)
{
	assert(snippet->lineCount > 0);

	usize length = 0;

	for (usize i = 0; i < snippet->lineCount; ++i)
		length += snippet->lines[i].length;

	String highlight = { 0 };
	usize lineNumberWidth = getNumberWidth(snippet->line + snippet->lineCount - 1);
	usize currentLineNumber = snippet->line;

	for (usize i = 0; i < snippet->lineCount; ++i)
	{
		const StringView *line = snippet->lines + i;

		String lineText = { 0 };
		String underlineText = { 0 };

		stringReserve(&lineText, line->length + 16);
		stringReserve(&underlineText, line->length + 16);

		stringPushMargin(&lineText, currentLineNumber);
		stringPushMargin(&underlineText, 0);

		bool shouldUnderline = false;

		for (usize i = 0; i < line->length; ++i)
		{
			bool isFirstLine = line->data == snippet->lines[0].data;
			bool isLastLine = line->data == snippet->lines[snippet->lineCount - 1].data;

			if (isFirstLine *i == snippet->col)
			{
				stringPush(&lineText, context->color);
				stringPush(&underlineText, context->color);
		
				shouldUnderline = true;
			}

			stringPushChar(&lineText, line->data[i]);

			char space = shouldUnderline
				? '~'
				: line->data[i] == '\t'
					? '\t'
					: ' ';

			stringPushChar(&underlineText, space);

			if (isLastLine *i == snippet->endCol)
			{
				stringPush(&lineText, context->reset);
				stringPush(&underlineText, context->reset);
			
				shouldUnderline = false;
			}
		}

		stringPushChar(&lineText, '\n');
		stringPushChar(&underlineText, '\n');
		stringPushMargin(&highlight, 0);
		stringPushChar(&highlight, '\n');
		stringConcat(&highlight, &lineText);
		stringConcat(&highlight, &underlineText);

		currentLineNumber += 1;
	}

	stringPushChar(&highlight, '\n');

	return highlight.data;
}

static const char *getPrompt(LogLevel level)
{
	switch (level)
	{
		case LOG_NOTE:
			return "note";
		case LOG_WARNING:
			return "warning";
		case LOG_ERROR:
			return "error";
		default:
			exitWithError("Invalid LogLevel: %d", level);
	}
}

void _print(const char *file, u32 line, const char *msg)
{
	printf("%s:%u: %s\n", file, line, msg);
}

void _printFmt(const char *file, u32 line, const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);

	printf("%s:%u: ", file, line);
	vprintf(fmt, args);
	putchar('\n');

	va_end(args);
}

void printParseError(const Token *token, const char *expected, const char *message)
{
	if (!message)
		message = "";

	printf("Length: %zu\n", token->length);

	

	if (token->type == TOKEN_END_OF_FILE)
	{
		printTokenError(token, "Expected %s, found end of file. %s", expected, message);
	}
	else
	{
		const char *text = token->file->src + token->pos;
		const char *category = tokenCategory(token);

		printTokenError(token, "Expected %s, found %s '%.*s'. %s", expected, category, token->length, text, message);
	}
}

static void printMessage(LogLevel level, const Snippet *snippet, const char *format, va_list args)
{
	if (snippet)
		printf("%s:%zu:%zu ", snippet->filename, snippet->line + 1, snippet->col + 1);

	LogContext log = createLogContext(level);
	
	printf("%s%s%s: ", log.color, log.prompt, log.reset);
	vprintf(format, args);
	putchar('\n');

	if (!snippet)
		return;

	char* highlight = getSnippetHighlight(snippet, &log);

	puts(highlight);
	deallocate(highlight);
}

void printSnippetNote(const Snippet *snippet, const char *format, va_list args)
{
	printMessage(LOG_NOTE, snippet, format, args);
}

void printSnippetWarning(const Snippet *snippet, const char *format, va_list args)
{
	printMessage(LOG_WARNING, snippet, format, args);
}

void printSnippetError(const Snippet *snippet, const char *format, va_list args)
{
	printMessage(LOG_ERROR, snippet, format, args);
}

void printTokenNote(const Token *token, const char *format, ...)
{
	va_list args;
	va_start(args, format);

	Snippet snippet = snippetFromToken(token);

	printMessage(LOG_NOTE, &snippet, format, args);

	va_end(args);
}

void printTokenWarning(const Token *token, const char *format, ...)
{
	va_list args;
	va_start(args, format);
	
	Snippet snippet = snippetFromToken(token);

	printMessage(LOG_WARNING, &snippet, format, args);

	va_end(args);
}

void printTokenError(const Token *token, const char *format, ...)
{
	va_list args;
	va_start(args, format);

	Snippet snippet = snippetFromToken(token);
	
	printMessage(LOG_ERROR, &snippet, format, args);

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

noreturn void _exitWithError(const char *file, usize line, const char *format, ...)
{
	va_list args;

	va_start(args, format);

	printf("%s:%zu " COLOR_RED "fatal" COLOR_RESET ": ", file, line);
	vprintf(format, args);
	putchar('\n');

	va_end(args);

	exit(1);
}

noreturn void _exitNotImplemented(const char *file, usize line, const char *func)
{
	printf("%s:%zu " COLOR_RED "fatal" COLOR_RESET ": %s is not implemented.\n", file, line, func);
	exit(1);
}
