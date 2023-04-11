#ifndef PARKA_ERROR_ERROR_HPP
#define PARKA_ERROR_ERROR_HPP

#include "parka/file/Highlight.hpp"

namespace parka
{
	enum class EntryType
	{
		Note,
		Warning,
		Error
	};

	class Entry
	{
		String _message;
		Optional<Highlight> _highlight;

		Error(String&& message) :
		_message(std::move(message))
		{}
		Error(StringMessagconst Highlight& highlight) :
		_highlight(highlight)
		{}

		friend struct Log;
	};
}

#endif
