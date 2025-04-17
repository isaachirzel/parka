#include "parka/enum/EntityType.hpp"

namespace parka
{
	const char *getEntityTypeText(EntityType entityType)
	{
		switch (entityType)
		{
			case EntityType::Package:
				return "package";

			case EntityType::Primitive:
				return "primitive";

			case EntityType::Struct:
				return "struct";

			case EntityType::Function:
				return "function";

			case EntityType::Variable:
				return "variable";

			case EntityType::Parameter:
				return "parameter";

			case EntityType::Member:
				return "member";

			default:
				break;
		}

		return "unknown";
	}

	std::ostream& operator<<(std::ostream& out, const EntityType& type)
	{
		const auto* text = getEntityTypeText(type);

		out << text;

		return out;
	}
}
