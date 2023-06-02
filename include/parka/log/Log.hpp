#ifndef PARKA_ERROR_ERROR_LOG_HPP
#define PARKA_ERROR_ERROR_LOG_HPP

#include "parka/enum/LogEntryType.hpp"
#include "parka/log/Highlight.hpp"
#include "parka/log/LogEntry.hpp"
#include "parka/util/Print.hpp"
#include "parka/util/SourceLocation.hpp"

namespace parka
{
	struct Log
	{
	private:

		static void addEntry(LogEntry&& entry);

	public:

		template <typename ...Arg>
		static void note(const char *fmt, Arg const&... args)
		{
			return addEntry(LogEntry(LogEntryType::Note, parka::format(fmt, args...)));
		}

		template <typename ...Arg>
		static void note(Highlight&& token, const char *fmt, Arg const&... args)
		{
			return addEntry(LogEntry(LogEntryType::Note, format(fmt, args...), token));
		}

		template <typename ...Arg>
		static void error(const char *format, Arg const&... args)
		{
			return addEntry(LogEntry(LogEntryType::Error, parka::format(format, args...)));
		}

		template <typename ...Arg>
		static void error(Highlight&& highlight, const char *format, Arg const&... args)
		{
			return addEntry(LogEntry(LogEntryType::Error, parka::format(format, args...), highlight));
		}

		static void parseError(const Token& token, const char *expected, const char *message = "");

		template <typename ...Arg>
		static void success(const char *format, Arg const&...args)
		{
			return addEntry(LogEntry(LogEntryType::Success, parka::format(format, args...)));
		}

		template <typename ...Arg>
		[[ noreturn ]]
		static void fatal(const char *format, Arg const&...args)
		{
			addEntry(LogEntry(LogEntryType::Fatal, parka::format(format, args...)));
			Log::outputEntries();
			exit(1);
		}

		[[ noreturn ]]
		static void notImplemented(SourceLocation&& location);

		static void outputEntries();

		// static void addNote(Token& token, const char *format);
		// static void addWarning(const char *format);
		// static void addWarning(Token& token, const char *format);
		// static void addError(const char *format);
		// static void addError(Token& token, const char *format);

		static bool isColorEnabled();

		static usize getNoteCount();
		static usize getSuccessCount();
		static usize getWarningCount();
		static usize getErrorCount();
		static usize getFatalCount();
	};
}

#endif
