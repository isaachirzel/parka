#include "parka/repository/EntitySyntaxId.hpp"

namespace parka
{
	const char *getEntityTypeText(EntityType type)
	{
		switch (type)
		{
			case EntityType::PackageSyntax:
				return "package";

			case EntityType::StructSyntax:
				return "struct";

			case EntityType::Primitive:
				return "primitive";

			case EntityType::Function:
				return "function";

			case EntityType::Variable:
				return "variable";

			case EntityType::ParameterSyntax:
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

	std::ostream& operator<<(std::ostream& out, const EntitySyntaxId& id)
	{

		out << id._type << "s[" << id._index << ']';

		return out;
	}

	bool EntitySyntaxId::operator==(const EntitySyntaxId& other) const
	{
		return _type == other.type() && _index == other.index();
	}
}
