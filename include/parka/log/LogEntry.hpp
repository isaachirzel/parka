#ifndef PARKA_ERROR_ERROR_HPP
#define PARKA_ERROR_ERROR_HPP

#include "parka/enum/LogEntryType.hpp"
#include "parka/file/Snippet.hpp"
#include "parka/util/Result.hpp"
#include "parka/util/String.hpp"
#include <ostream>

namespace parka
{
	class LogEntry
	{
		String _message;
		Result<Snippet> _snippet;
		LogEntryType _type;

	public:

		LogEntry(LogEntryType type, String&& message):
		_message(std::move(message)),
		_type(type)
		{}

		LogEntry(LogEntryType type, String&& message, const Snippet& snippet):
		_message(std::move(message)),
		_snippet(snippet),
		_type(type)
		{}

		const auto& message() const { return _message; }
		const auto& snippet() const { return _snippet; }
		const auto& type() const { return _type; }
		
		friend std::ostream& operator<<(std::ostream& out, const LogEntry& entry);
	};
}

#endif
