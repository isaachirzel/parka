#ifndef PARKA_UTIL_PRINT_HPP
#define PARKA_UTIL_PRINT_HPP

#include <iostream>
#include <stdexcept>

namespace parka
{
	void _output(std::ostream& out, const char * const fmt);

	template <typename First, typename... Arg>
	void _output(std::ostream& out, const char * const fmt, const First& first, Arg const&... args)
	{
		// TODO: Not giving argument for $ seems to cause silent crash?
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
			out << std::fixed;
		
		out << first;

		iter += 1;

		_output(out, iter, args...);
	}

	template <typename... Arg>
	void print(const char * const fmt, Arg const&... args)
	{
		_output(std::cout, fmt, args...);
	}

	template <typename... Arg>
	void println(const char * const fmt, Arg const&... args)
	{
		_output(std::cout, fmt, args...);

		std::cout << std::endl;
	}
}

#endif
