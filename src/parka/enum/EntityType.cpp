#include "parka/enum/EntityType.hpp"


namespace parka
{
	static const char *getEntityTypeText(EntityType type)
	{
		switch (type)
		{
			case EntityType::Package:
				return "package";

			case EntityType::Struct:
				return "struct";

			case EntityType::Primitive:
				return "primitive";

			case EntityType::Function:
				return "function";

			case EntityType::Variable:
				return "variable";

			case EntityType::Parameter:
				return "parameter";
			
			default:
				return "";
		}
	}

	std::ostream& operator<<(std::ostream& out, const EntityType& type)
	{
		const auto *text = getEntityTypeText(type);

		out << text;

		return out;
	}
}
