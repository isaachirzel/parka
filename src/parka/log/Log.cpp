#include "parka/log/Log.hpp"
#include "parka/log/LogEntry.hpp"
#include "parka/util/Common.hpp"
#include "parka/util/Pool.hpp"
#include "parka/util/Table.hpp"

#include <iostream>

namespace parka
{
	namespace log
	{
		usize noteCount = 0;
		usize successCount = 0;
		usize warningCount = 0;
		usize errorCount = 0;
		usize fatalCount = 0;
		Pool<LogEntry> entries(1'000'000);

		Table<usize, usize> entryTable;
	}
	// TODO: Organize by files
	// TODO: Thread safety
	
	void Log::addEntry(LogEntry&& entry)
	{
		switch (entry._type)
		{
			case LogEntryType::Note:
				log::noteCount += 1;
				break;

			case LogEntryType::Success:
				log::successCount += 1;
				break;

			case LogEntryType::Warning:
				log::warningCount += 1;
				break;

			case LogEntryType::Error:
				log::warningCount += 1;
				break;

			case LogEntryType::Fatal:
				log::fatalCount += 1;
				break;
		}

		auto filePtr = entry._highlight
			? (usize)&entry._highlight->position().file()
			: 0;
		auto entryIndex = log::entries.add(std::move(entry));

		log::entryTable.insert(filePtr, entryIndex);
	}

	void Log::parseError(const Token& token, const char *expected, const char *message)
	{
		assert(expected != nullptr);
		assert(message != nullptr);

		Log::error(token, "Expected $, found $. $", expected, token.type(), message);
	}

	void Log::notImplemented(SourceLocation &&location)
	{
		addEntry(LogEntry(LogEntryType::Fatal, parka::format("$ is not implemented.", location)));
		Log::outputEntries();
		exit(1);
	}

	void Log::outputEntries()
	{
		for (const auto& entry : log::entries)
		{
			std::cout << entry;
		}
	}

	usize Log::getNoteCount() { return log::noteCount; }
	usize Log::getSuccessCount() { return log::successCount; }
	usize Log::getWarningCount() { return log::warningCount; }
	usize Log::getErrorCount() { return log::errorCount; }
	usize Log::getFatalCount() { return log::fatalCount; }
}
