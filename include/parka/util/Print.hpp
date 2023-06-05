#ifndef PARKA_UTIL_PRINT_HPP
#define PARKA_UTIL_PRINT_HPP

#include "parka/Token.hpp"
#include "parka/enum/LogEntryType.hpp"
#include "parka/log/Prompt.hpp"
#include "parka/util/SourceLocation.hpp"
#include <iostream>
#include <stdexcept>

namespace parka
{
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
					// TODO: put argument in exception message
					throw std::runtime_error("No format specifier was given for argument");

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
		_output(std::cout, fmt, args...);

		std::cout << std::endl;
	}

	template <typename... Arg>
	String format(const char * fmt, Arg const&... args)
	{
		std::ostringstream out;

		_output(out, fmt, args...);

		return out.str();
	}
}

#endif
