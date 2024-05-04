#ifndef PARKA_ERROR_ERROR_HPP
#define PARKA_ERROR_ERROR_HPP

#include "parka/enum/LogEntryType.hpp"
#include "parka/file/Snippet.hpp"
#include "parka/log/Color.hpp"
#include "parka/util/Result.hpp"
#include "parka/util/String.hpp"
#include <ostream>

namespace parka
{
	class LogEntry
	{
		String _message;
		Result<Snippet> _snippet;
		Color _color;
		LogEntryType _type;

		static Color getColor(LogEntryType type);

	public:

		LogEntry(LogEntryType type, String&& message):
		_message(std::move(message)),
		_color(getColor(type)),
		_type(type)
		{}

		LogEntry(LogEntryType type, String&& message, const Snippet& snippet):
		_message(std::move(message)),
		_snippet(snippet),
		_color(getColor(type)),
		_type(type)
		{}

		const auto& message() const { return _message; }
		const auto& snippet() const { return _snippet; }
		const auto& color() const { return _color; }
		const auto& type() const { return _type; }
		
		friend std::ostream& operator<<(std::ostream& out, const LogEntry& entry);
	};
}

#endif
