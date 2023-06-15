#include "parka/log/Log.hpp"
#include "parka/log/ArenaStreamBuffer.hpp"
#include "parka/log/LogEntry.hpp"
#include "parka/util/Arena.hpp"
#include "parka/util/Common.hpp"
#include "parka/util/Pool.hpp"
#include "parka/util/Table.hpp"
#include <ostream>

namespace parka::log
{
	usize noteCount = 0;
	usize successCount = 0;
	usize warningCount = 0;
	usize errorCount = 0;
	usize fatalCount = 0;
	Pool<LogEntry> entries(1'000'000);
	Table<usize, usize> entryTable;

	// TODO: Organize by files
	// TODO: Thread safety
	
	void addEntry(LogEntry&& entry)
	{
		switch (entry.type())
		{
			case LogEntryType::Success:
				log::successCount  += 1;
				break;

			case LogEntryType::Note:
				log::noteCount += 1;
				break;

			case LogEntryType::Warning:
				log::warningCount += 1;
				break;

			case LogEntryType::Error:
				log::errorCount += 1;
				break;

			case LogEntryType::Fatal:
				log::fatalCount += 1;
				break;
		}

		// TODO: Sort the entries by using :
		//entry.snippet()->position().file().path();
		// as key so that when validation of that file is complete,
		// it can dump them into the console

		// auto filePtr = entry.snippet()
		// 	? (usize)&entry.snippet()->position().file()
		// 	: 0; // No file association
		// log::entries.add(std::move(entry));

		// log::entryTable.insert(filePtr, entryIndex);

		std::cout << entry;
	}

	void parseError(const Token& token, const char *expected, const char *message)
	{
		assert(expected != nullptr);
		assert(message != nullptr);

		log::error(token, "Expected $, found $. $", expected, token.type(), message);
	}

	void outputEntries()
	{
		for (const auto& entry : entries)
		{
			std::cout << entry;
		}
	}

	void notImplemented(SourceLocation&& location)
	{
		addEntry(LogEntry(LogEntryType::Fatal, parka::format("$ is not implemented.", location)));
		outputEntries();
		exit(1);
	}

	// Arena generate()
	// {
	// 	auto buffer = ArenaStreamBuffer(1 << 30); // 1 GB
	// 	auto stream = std::ostream(&buffer);
	// 	Array<Color*> colors;
	// 	usize indent = 0;
	// 	usize lineNumber = 0;

	// 	// TODO: Sort entries
	// 	for (const auto& entry : log::entries)
	// 	{
	// 		stream << entry;
	// 	}


	// 	return buffer;
	// }

	usize getNoteCount() { return noteCount; }
	usize getSuccessCount() { return successCount; }
	usize getWarningCount() { return warningCount; }
	usize getErrorCount() { return errorCount; }
	usize getFatalCount() { return fatalCount; }
}
