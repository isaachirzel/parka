#include "parka/enum/EntityType.hpp"

namespace parka
{
	std::ostream& operator<<(std::ostream& out, const EntityType& type)
	{
		switch (type)
		{
			case EntityType::Package:
				out << "package";
				break;

			case EntityType::Primitive:
				out << "primitive";
				break;

			case EntityType::Struct:
				out << "struct";
				break;

			case EntityType::Function:
				out << "function";
				break;

			case EntityType::Variable:
				out << "variable";
				break;

			case EntityType::Parameter:
				out << "parameter";
				break;

			case EntityType::Member:
				out << "member";
				break;
		}

		return out;
	}
}
