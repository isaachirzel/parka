#include "parka/symbol/entity_id.hpp"

const char *getEntityTypeText(EntityType type)
{
	switch (type)
	{
		case EntityType::Package:
			return "Package";

		case EntityType::Struct:
			return "Struct";

		case EntityType::Primitive:
			return "Primitive";

		case EntityType::Function:
			return "Function";

		case EntityType::Variable:
			return "Variable";

		case EntityType::Parameter:
			return "Parameter";
		
		default:
			return "";
	}
}

std::ostream& operator<<(std::ostream& out, const EntityId& id)
{
	const auto *text = getEntityTypeText(id._type);

	out << text << "s[" << id._index << ']';

	return out;
}

bool EntityId::operator==(const EntityId& other) const
{
	return _type == other.type() && _index == other.index();
}
