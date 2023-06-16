#include "parka/enum/EntityType.hpp"

namespace parka
{
	std::ostream& operator<<(std::ostream& out, const EntityType& type)
	{
		switch (type)
		{
			case EntityType::Member:
				out << "member";
				break;

			case EntityType::Variable:
				out << "variable";
				break;

			case EntityType::Parameter:
				out << "parameter";
				break;
			
			default:
				out << "(" << (int)type << ") Invalid";
				break;
		}

		return out;
	}
}
