#ifndef PARKA_ERROR_ERROR_HPP
#define PARKA_ERROR_ERROR_HPP

#include "parka/enum/Severity.hpp"
#include "parka/log/CodeView.hpp"
#include "parka/util/Optional.hpp"
#include "parka/util/String.hpp"
#include <ostream>

namespace parka
{
	class LogEntry
	{
		String _message;
		Optional<CodeView> _view;
		Severity _type;

	public:

		LogEntry(Severity type, String&& message):
			_message(std::move(message)),
			_view(),
			_type(type)
		{}

		LogEntry(Severity type, String&& message, CodeView&& view):
			_message(std::move(message)),
			_view(std::move(view)),
			_type(type)
		{}

		const auto& message() const { return _message; }
		const auto& view() const { return _view; }
		const auto& type() const { return _type; }
		
		friend std::ostream& operator<<(std::ostream& out, const LogEntry& entry);
	};
}

#endif
