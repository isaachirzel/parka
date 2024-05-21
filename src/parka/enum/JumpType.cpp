#include "parka/enum/JumpType.hpp"

namespace parka
{
	std::ostream& operator<<(std::ostream& out, const JumpType& type)
	{
		switch (type)
		{
			case JumpType::None:
				out << "none";
				break;

			case JumpType::Return:
				out << "return";
				break;

			default:
				out << "(Invalid " << (int)type << ")";
				break;
		}

		return out;
	}
}
