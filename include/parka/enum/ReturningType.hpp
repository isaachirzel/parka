#ifndef PARKA_ENUM_RETURNING_TYPE_HPP
#define PARKA_ENUM_RETURNING_TYPE_HPP

#include <ostream>
namespace parka
{
	enum class ReturningType
	{
		None,
		Return
	};

	std::ostream& operator<<(std::ostream& out, const ReturningType& type);
}

#endif
