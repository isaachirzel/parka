#ifndef PARKA_ERROR_ERROR_LOG_HPP
#define PARKA_ERROR_ERROR_LOG_HPP

#include "parka/enum/LogEntryType.hpp"
#include "parka/file/Snippet.hpp"
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
	void debug(const char *fmt, Arg const&... args)
	{
		#ifndef NDEBUG
		return addEntry(LogEntry(LogEntryType::Debug, parka::format(fmt, args...)));
		#endif
	}

	template <typename ...Arg>
	void debug(const Snippet& token, const char *fmt, Arg const&... args)
	{
		#ifndef NDEBUG
		return addEntry(LogEntry(LogEntryType::Debug, format(fmt, args...), token));
		#endif
	}

	template <typename ...Arg>
	void note(const char *fmt, Arg const&... args)
	{
		return addEntry(LogEntry(LogEntryType::Note, parka::format(fmt, args...)));
	}

	template <typename ...Arg>
	void note(const Snippet& token, const char *fmt, Arg const&... args)
	{
		return addEntry(LogEntry(LogEntryType::Note, format(fmt, args...), token));
	}

	template <typename ...Arg>
	void error(const char *format, Arg const&... args)
	{
		return addEntry(LogEntry(LogEntryType::Error, parka::format(format, args...)));
	}

	template <typename ...Arg>
	void error(const Snippet& snippet, const char *format, Arg const&... args)
	{
		return addEntry(LogEntry(LogEntryType::Error, parka::format(format, args...), snippet));
	}

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
		exit(1);
	}

	template <typename ...Arg>
	[[ noreturn ]]
	void fatal(const Snippet& snippet, const char *format, Arg const&...args)
	{
		addEntry(LogEntry(LogEntryType::Fatal, parka::format(format, args...), snippet));
		exit(1);
	}

	[[ noreturn ]]
	void notImplemented(SourceLocation&& location);

	usize getDebugCount();
	usize getNoteCount();
	usize getSuccessCount();
	usize getWarningCount();
	usize getErrorCount();
	usize getFatalCount();
}

#endif
