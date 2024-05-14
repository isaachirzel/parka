#include "parka/enum/AssignmentType.hpp"
namespace parka
{
	std::ostream& operator<<(std::ostream& out, const AssignmentType& type)
	{
		switch (type)
		{
			case AssignmentType::Assign:
				out << "=";
				break;

			default:
				out << "(Invalid) " << (int)type;
		}

		return out;
	}
}
