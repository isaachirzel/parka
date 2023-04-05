#include "parka/symbol/typed_entity_id.hpp"

Optional<TypedEntityId> TypedEntityId::from(const EntityId& id)
{
	switch (id.type())
	{
		case EntityType::Struct:
			return TypedEntityId(TypedEntityType::Struct, id.index());

		case EntityType::Primitive:
			return TypedEntityId(TypedEntityType::Primitive, id.index());

		case EntityType::Function:
			return TypedEntityId(TypedEntityType::Function, id.index());

		case EntityType::Variable:
			return TypedEntityId(TypedEntityType::Variable, id.index());

		case EntityType::Parameter:
			return TypedEntityId(TypedEntityType::Parameter, id.index());

		default:
			return {};
	}
}

const char *getTypedEntityTypeText(TypedEntityType type)
{
	switch (type)
	{
		case TypedEntityType::Struct:
			return "Struct";

		case TypedEntityType::Primitive:
			return "Primitive";

		case TypedEntityType::Function:
			return "Function";

		case TypedEntityType::Variable:
			return "Variable";

		case TypedEntityType::Parameter:
			return "Parameter";
		
		default:
			return "";
	}
}

std::ostream& operator<<(std::ostream& out, const TypedEntityId& id)
{
	out << getTypedEntityTypeText(id.type());

	out << "s[" << id.index() << ']';

	return out;
}

bool TypedEntityId::operator==(const TypedEntityId& other) const
{
	return _type == other._type && _index == other._index;
}
