#ifndef PARKA_AST_TYPE_TYPE_KEY_HPP
#define PARKA_AST_TYPE_TYPE_KEY_HPP

#include "parka/ast/type/type_id.hpp"
#include "parka/util/primitives.hpp"
#include <functional>

class TypeKey
{
	TypeId _id;

public:

	TypeKey(const TypeId id) :
	_id(id)
	{}
	TypeKey(TypeKey&&) = default;
	TypeKey(const TypeKey&) = default;
	~TypeKey() = default;

	u64 hash() const;
	const auto& id() const { return _id; }

	friend bool operator==(const TypeKey& left, const TypeKey& right);
};

template <>
u64 hash64(const TypeKey& key);

namespace std
{
	template <>
	struct hash<TypeKey>
	{
		usize operator()(const TypeKey& key) const { return hash64(key); }
	};
}


#endif
