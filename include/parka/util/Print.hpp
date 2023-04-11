#ifndef PARKA_UTIL_PRINT_HPP
#define PARKA_UTIL_PRINT_HPP

#include "parka/Token.hpp"
#include "parka/util/Prompt.hpp"
#include "parka/util/SourceLocation.hpp"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <type_traits>

namespace parka
{
	void addError();

	void _output(std::ostream& out, const char * const fmt);

	template <typename First, typename... Arg>
	void _output(std::ostream& out, const char * const fmt, const First& first, Arg const&... args)
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

		out.write(fmt, iter - fmt);

		if constexpr (std::is_floating_point_v<First>)
		{
			out << std::fixed;
		}
		
		out << first;

		iter += 1;

		_output(out, iter, args...);
	}

	template <typename... Arg>
	void print(const char * const fmt, Arg const&... args)
	{
		return _output(std::cout, fmt, args...);
	}

	template <typename... Arg>
	String format(const char * fmt, Arg const&... args)
	{
		std::ostringstream out;

		_output(out, fmt, args...);

		return out.str();
	}

	String toHighlight(const Token& token, const FilePosition& position, const Prompt& prompt);
	void printPrompt(const Prompt& prompt, const FilePosition& position);

	template <PromptType type, typename... Arg>
	void printMessage(const char *format, Arg const&... args)
	{
		auto prompt = Prompt(type);

		if constexpr (type == PromptType::Error)
		{
			addError();
		}

		std::cout << prompt << ' ';

		_output(std::cout, format, args...);
	}
	template <typename... Arg>
	void printNote(const char* format, Arg const&... args) { printMessage<PromptType::Note>(format, args...); }
	template <typename... Arg>
	void printWarning(const char *format, Arg const&... args) { printMessage<PromptType::Warning>(format, args...); }
	template <typename... Arg>
	void printError(const char *format, Arg const&... args) { printMessage<PromptType::Error>(format, args...); }
	template <typename... Arg>
	void printSuccess(const char *format, Arg const&... args) { printMessage<PromptType::Success>(format, args...); }

	template <PromptType type, typename... Arg>
	void printTokenMessage(const Token& token, const char *format, Arg const&... args)
	{
		auto prompt = Prompt(type);
		auto position = token.getFilePosition();

		if constexpr (type == PromptType::Error)
		{
			addError();
		}

		std::cout << token.file().path() << ':' << position << ' ' << prompt << ' ';

		_output(std::cout, format, args...);

		std::cout << toHighlight(token, position, prompt);
	}
	template <typename... Arg>
	void printNote(const Token& token, const char *format, Arg const&... args) { printTokenMessage<PromptType::Note>(token, format, args...); }
	template <typename... Arg>
	void printWarning(const Token& token, const char *format, Arg const&... args) { printTokenMessage<PromptType::Warning>(token, format, args...); }
	template <typename... Arg>
	void printError(const Token& token, const char *format, Arg const&... args) { printTokenMessage<PromptType::Error>(token, format, args...); }

	void printParseError(const Token& token, const char *expected, const char *message = "");

	void enableColorPrinting(bool enabled);
	bool isColorPrintingEnabled();
	usize getNoteCount();
	usize getWarningCount();
	usize getErrorCount();

	template <typename ...Arg>
	[[ noreturn ]]
	void exitWithError(const char *fmt, Arg... args)
	{
		_output(std::cout, fmt, args...);
		exit(1);
	}

	[[ noreturn ]]
	void exitNotImplemented(SourceLocation&& location);
}

#endif
