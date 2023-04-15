#include "parka/util/Path.hpp"
#include "parka/util/Print.hpp"
#include "parka/util/Common.hpp"
#include "parka/util/String.hpp"

#include <iostream> 
#include <cstdarg>
#include <cstring>

namespace parka
{	
	usize findOccurrence(const char *text, const char *token)
	{
		assert(text != nullptr);
		assert(token != nullptr);

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

	void _output(std::ostream& out, const char * const fmt)
	{
		for (const char * iter = fmt; *iter; ++iter)
		{
			if (*iter == '$' && iter > fmt && iter[-1] != '\\')
			{
				out << "Not enough arguments to print." << std::endl;
				exit(1);
			}
		}

		out << fmt;
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
		std::cout << Prompt::Fatal << ' ';

		print("$ is not implemented.", location.function());
		exit(1);
	}
}
