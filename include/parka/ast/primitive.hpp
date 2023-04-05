#ifndef PARKA_AST_PRIMITIVE_HPP
#define PARKA_AST_PRIMITIVE_HPP

#include "parka/node/entity.hpp"
#include "parka/node/node_bank.hpp"
#include "parka/node/typed_entity.hpp"
#include "parka/token.hpp"
#include "parka/util/array.hpp"
#include "parka/util/primitives.hpp"
#include "parka/util/string.hpp"

enum class PrimitiveType
{
	Void,
	UnsignedInteger,
	SignedInteger,
	FloatingPoint,
	Boolean,
	Character,
	String
};

class Primitive : public Entity
{
	String _identifier;
	PrimitiveType _type;
	u32 _size;

	Primitive(const char *identifier, PrimitiveType type, u32 size) :
	_identifier(identifier),
	_type(type),
	_size(size)
	{}

public:

	Primitive(Primitive&&) = default;
	Primitive(const Primitive&) = delete;
	~Primitive() = default;

	const String& identifier() const { return _identifier; }
	EntityType type() const { return EntityType::Primitive; }
	const auto& primitiveType() const { return _type; }
	const auto& size() const { return _size; }

	friend struct NodeBank;
};

#endif
