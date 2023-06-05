#ifndef PARKA_ERROR_ERROR_LOG_HPP
#define PARKA_ERROR_ERROR_LOG_HPP

#include "parka/enum/LogEntryType.hpp"
#include "parka/log/Highlight.hpp"
#include "parka/log/LogEntry.hpp"
#include "parka/util/Print.hpp"
#include "parka/util/SourceLocation.hpp"


/*
	Colors
	Indent
	Line number for margins
*/


namespace parka::log
{
	extern void addEntry(LogEntry&& entry);

	template <typename ...Arg>
	void note(const char *fmt, Arg const&... args)
	{
		return addEntry(LogEntry(LogEntryType::Note, parka::format(fmt, args...)));
	}

	template <typename ...Arg>
	void note(Highlight&& token, const char *fmt, Arg const&... args)
	{
		return addEntry(LogEntry(LogEntryType::Note, format(fmt, args...), token));
	}

	template <typename ...Arg>
	void error(const char *format, Arg const&... args)
	{
		return addEntry(LogEntry(LogEntryType::Error, parka::format(format, args...)));
	}

	template <typename ...Arg>
	void error(Highlight&& highlight, const char *format, Arg const&... args)
	{
		return addEntry(LogEntry(LogEntryType::Error, parka::format(format, args...), highlight));
	}

	void parseError(const Token& token, const char *expected, const char *message = "");

	template <typename ...Arg>
	void success(const char *format, Arg const&...args)
	{
		return addEntry(LogEntry(LogEntryType::Success, parka::format(format, args...)));
	}

	template <typename ...Arg>
	[[ noreturn ]]
	void fatal(const char *format, Arg const&...args)
	{
		addEntry(LogEntry(LogEntryType::Fatal, parka::format(format, args...)));
		// FIXME: Output entries
		// log::outputEntries();
		exit(1);
	}

	[[ noreturn ]]
	void notImplemented(SourceLocation&& location);

	usize getNoteCount();
	usize getSuccessCount();
	usize getWarningCount();
	usize getErrorCount();
	usize getFatalCount();
}

#endif
