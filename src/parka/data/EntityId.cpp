#include "parka/data/EntityId.hpp"

namespace parka
{
	const char *getEntityTypeText(EntityType type)
	{
		switch (type)
		{
			case EntityType::PackageSyntax:
				return "PackageSyntax";

			case EntityType::StructSyntax:
				return "StructSyntax";

			case EntityType::Primitive:
				return "Primitive";

			case EntityType::Function:
				return "FunctionSyntax";

			case EntityType::Variable:
				return "VariableSyntax";

			case EntityType::ParameterSyntax:
				return "ParameterSyntax";
			
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

	std::ostream& operator<<(std::ostream& out, const EntityId& id)
	{

		out << id._type << "s[" << id._index << ']';

		return out;
	}

	bool EntityId::operator==(const EntityId& other) const
	{
		return _type == other.type() && _index == other.index();
	}
}
