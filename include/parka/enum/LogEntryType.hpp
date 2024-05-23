#ifndef PARKA_ENUM_ENTRY_TYPE_HPP
#define PARKA_ENUM_ENTRY_TYPE_HPP

#include "parka/util/Common.hpp"

namespace parka
{
	enum class LogEntryType: u8
	{
		Debug,
		Note,
		Success,
		Warning,
		Error,
		Fatal
	};

	// TODO: Create print function
}

#endif
