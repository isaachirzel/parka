#ifndef PARKA_AST_TYPE_TYPE_ID_HPP
#define PARKA_AST_TYPE_TYPE_ID_HPP

#include "parka/symbol/entity_id.hpp"
#include "parka/util/hash.hpp"
#include "parka/util/primitives.hpp"
#include <cassert>

enum class TypeType : u8
{
	Primitive,
	Struct
};

class TypeId
{
	TypeType _type;
	u32 _index;

public:

	TypeId(TypeType type, usize index) :
	_type(type),
	_index(index)
	{}
	TypeId(TypeId&&) = default;
	TypeId(const TypeId&) = default;
	~TypeId() = default;

	const auto& type() const { return _type; }
	const auto& index() const { return _index; }

	friend bool operator==(const TypeId& left, const TypeId& right);
};

template <>
u32 hash32(const TypeId& id);

template <>
u64 hash64(const TypeId& id);

#endif