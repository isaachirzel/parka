#include "parka/util/path.hpp"
#include "parka/util/print.hpp"
#include "parka/util/primitives.hpp"
#include "parka/util/string.hpp"

#include <iostream> 
#include <cstdarg>
#include <cstring>

bool isColorEnabled = true;
usize errorCount = 0;
usize warningCount = 0;
usize noteCount = 0;

bool isColorPrintingEnabled()
{
	return isColorEnabled;
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

String toHighlight(const Token& token, const FilePosition& position, const Prompt& prompt)
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
	if (prompt.color())
	{
		line += prompt.color();
		underline += prompt.color();
	}

	line += token.text();
	underline += String(token.length(), '~');

	// Reset
	if (*prompt.color())
	{
		line += prompt.reset();
		underline += prompt.reset();
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

	printError(token, "Expected $, found $. $", expected, token.type(), message);
}

[[ noreturn ]]
void exitNotImplemented(SourceLocation&& location)
{
	std::cout << location;
	std::cout << Prompt(PromptType::Fatal);

	print("$ is not implemented.", location.function());
	exit(1);
}

usize getNoteCount()
{
	return noteCount;
}

usize getWarningCount()
{
	return warningCount;
}

usize getErrorCount()
{
	return errorCount;
}
