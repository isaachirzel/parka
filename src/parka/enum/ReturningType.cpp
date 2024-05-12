#include "parka/enum/ReturningType.hpp"

namespace parka
{
	std::ostream& operator<<(std::ostream& out, const ReturningType& type)
	{
		switch (type)
		{
			case ReturningType::None:
				out << "none";
				break;

			case ReturningType::Return:
				out << "return";
				break;

			default:
				out << "(Invalid " << (int)type << ")";
				break;
		}

		return out;
	}
}
