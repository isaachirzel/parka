#ifndef PARKA_UTIL_PRINT_HPP
#define PARKA_UTIL_PRINT_HPP

#include "parka/token.hpp"
#include "parka/util/prompt.hpp"
#include "parka/util/source_location.hpp"

#include <iostream>
#include <cstdlib>

void _print(const char * const fmt);

template <typename First, typename... Arg>
void _print(const char * const fmt, const First& first, Arg const&... args)
{
	// TODO: Escape $ symbol
	const char *iter = fmt;

	while (true)
	{
		switch (*iter)
		{
			case '$':
				break;

			case '\0':
				// std::cout << fmt << "<--" << std::endl;
				// TODO: put argument in exception message
				std::cout << "Not format specifier was given for argument: " << first << std::endl;
				exit(1);

			default:
				iter += 1;
				continue;
		}

		break;
	}

	std::cout.write(fmt, iter - fmt);
	std::cout << first;

	iter += 1;

	_print(iter, args...);
}

template <typename... Arg>
void print(const char * const fmt, Arg const&... args)
{
	return _print(fmt, args...);
}

[[ noreturn ]]
void exitNotImplemented(SourceLocation&& location);
void enableColorPrinting(bool enabled);
void printPrompt(PromptType type);

void printTokenNote(const Token& token, const char *format, ...);
void printTokenWarning(const Token& token, const char *format, ...);
void printTokenError(const Token& token, const char *format, ...);

template <PromptType type, typename... Arg>
void printMessage(const char *format, Arg const&... args)
{
	std::cout << Prompt(type);
	print(format, args...);
}
template <typename... Arg>
void printNote(const char* format, Arg const&... args) { printMessage<PromptType::Note>(format, args...); }
template <typename... Arg>
void printWarning(const char *format, Arg const&... args) { printMessage<PromptType::Warning>(format, args...); }
template <typename... Arg>
void printError(const char *format, Arg const&... args) { printMessage<PromptType::Error>(format, args...); }
template <typename... Arg>
void printSuccess(const char *format, Arg const&... args) { printMessage<PromptType::Success>(format, args...); }

void printParseError(const Token& token, const char *expected, const char *message = NULL);

usize getNoteCount();
usize getWarningCount();
usize getErrorCount();

template <typename ...Arg>
[[ noreturn ]]
void exitWithError(const char *fmt, Arg... args)
{
	_print(fmt, args...);
	exit(1);
}


#endif
