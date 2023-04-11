#ifndef PARKA_SYNTAX_TYPE_TYPE_KEY_SYNTAX_HPP
#define PARKA_SYNTAX_TYPE_TYPE_KEY_SYNTAX_HPP

#include "parka/repository/TypeId.hpp"
#include "parka/util/Primitives.hpp"

#include <functional>

namespace parka
{
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
}

namespace std
{
	template <>
	struct hash<parka::TypeKey>
	{
		parka::usize operator()(const parka::TypeKey& key) const { return hash64(key); }
	};
}


#endif
