#ifndef PARKA_AST_PRIMITIVE_HPP
#define PARKA_AST_PRIMITIVE_HPP

#include "parka/entity/entity.hpp"
#include "parka/token.hpp"
#include "parka/util/array.hpp"
#include "parka/util/primitives.hpp"
#include "parka/util/string.hpp"

enum PrimitiveIndex
{
	INDEX_VOID,
	INDEX_U8,
	INDEX_16,
	INDEX_U32,
	INDEX_U64,
	INDEX_I8,
	INDEX_I16,
	INDEX_I32,
	INDEX_I64,
	INDEX_F32,
	INDEX_F64,
	INDEX_BOOL,
	INDEX_CHAR,
	INDEX_STRING,
};

enum PrimitiveType
{
	PRIMITIVE_VOID,
	PRIMITIVE_UNSIGNED_INTEGER,
	PRIMITIVE_SIGNED_INTEGER,
	PRIMITIVE_FLOATING_POINT,
	PRIMITIVE_BOOLEAN,
	PRIMITIVE_CHARACTER,
	PRIMITIVE_STRING
};

class Primitive : public Entity
{
	String _symbol;
	PrimitiveType _type;
	u32 _size;

public:

	Primitive(const char *symbol, PrimitiveType type, u32 size) :
	_symbol(symbol),
	_type(type),
	_size(size)
	{}
	Primitive(Primitive&&) = default;
	Primitive(const Primitive&) = delete;

	Token token() const;
	const String& symbol() const { return _symbol; }
	EntityType type() const { return EntityType::Primitive; }
	const auto& primitiveType() const { return _type; }
	const auto& size() const { return _size; }
};

#endif
