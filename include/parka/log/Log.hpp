#ifndef PARKA_ERROR_ERROR_LOG_HPP
#define PARKA_ERROR_ERROR_LOG_HPP

#include "parka/log/Highlight.hpp"
#include "parka/log/LogEntry.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	struct Log
	{
	private:

		static void addEntry(LogEntry&& entry);

	public:

		template <typename ...Arg>
		static void addNote(const char *fmt, Arg const&... args)
		{
			return addEntry(LogEntry(LogEntryType::Note, format(fmt, args...)));
		}

		template <typename ...Arg>
		static void addNote(Highlight&& token, const char *fmt, Arg const&... args)
		{
			return addEntry(LogEntry(LogEntryType::Note, format(fmt, args...), token));
		}

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
