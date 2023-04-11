// #include "parka/data/TypedEntityId.hpp"

// namespace parka
// {
// 	Optional<TypedEntityId> TypedEntityId::from(const EntityId& id)
// 	{
// 		switch (id.type())
// 		{
// 			case EntityType::StructSyntax:
// 				return TypedEntityId(TypedEntityType::StructSyntax, id.index());

// 			case EntityType::Primitive:
// 				return TypedEntityId(TypedEntityType::Primitive, id.index());

// 			case EntityType::Function:
// 				return TypedEntityId(TypedEntityType::Function, id.index());

// 			case EntityType::Variable:
// 				return TypedEntityId(TypedEntityType::Variable, id.index());

// 			case EntityType::ParameterSyntax:
// 				return TypedEntityId(TypedEntityType::ParameterSyntax, id.index());

// 			default:
// 				return {};
// 		}
// 	}

// 	const char *getTypedEntityTypeText(TypedEntityType type)
// 	{
// 		switch (type)
// 		{
// 			case TypedEntityType::StructSyntax:
// 				return "StructSyntax";

// 			case TypedEntityType::Primitive:
// 				return "Primitive";

// 			case TypedEntityType::Function:
// 				return "FunctionSyntax";

// 			case TypedEntityType::Variable:
// 				return "VariableSyntax";

// 			case TypedEntityType::ParameterSyntax:
// 				return "ParameterSyntax";
			
// 			default:
// 				return "";
// 		}
// 	}

// 	std::ostream& operator<<(std::ostream& out, const TypedEntityId& id)
// 	{
// 		out << getTypedEntityTypeText(id.type());

// 		out << "s[" << id.index() << ']';

// 		return out;
// 	}

// 	bool TypedEntityId::operator==(const TypedEntityId& other) const
// 	{
// 		return _type == other._type && _index == other._index;
// 	}
// }
