#ifndef PARKA_ERROR_ERROR_HPP
#define PARKA_ERROR_ERROR_HPP

#include "parka/enum/LogEntryType.hpp"
#include "parka/log/Highlight.hpp"
#include "parka/util/Optional.hpp"
#include "parka/util/String.hpp"
#include <ostream>

namespace parka
{
	class LogEntry
	{
		String _message;
		Optional<Highlight> _highlight;
		Color _color;
		LogEntryType _type;

		static Color getColor(LogEntryType type);

	public:

		LogEntry(LogEntryType type, String&& message) :
		_message(std::move(message)),
		_color(getColor(type)),
		_type(type)
		{}

		LogEntry(LogEntryType type, String&& message, const Highlight& highlight) :
		_message(std::move(message)),
		_highlight(highlight),
		_color(getColor(type)),
		_type(type)
		{}

		const auto& message() const { return _message; }
		const auto& highlight() const { return _highlight; }
		const auto& color() const { return _color; }
		const auto& type() const { return _type; }
		
		friend std::ostream& operator<<(std::ostream& out, const LogEntry& entry);
	};
}

#endif
