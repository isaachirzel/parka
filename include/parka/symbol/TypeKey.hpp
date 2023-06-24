#ifndef PARKA_AST_TYPE_TYPE_KEY_HPP
#define PARKA_AST_TYPE_TYPE_KEY_HPP

#include "parka/repository/TypeId.hpp"
#include "parka/util/Common.hpp"

#include <functional>

namespace parka
{
	class TypeKey
	{
		TypeId _id;

	public:

		TypeKey(const TypeId id):
		_id(id)
		{}
		TypeKey(TypeKey&&) = default;
		TypeKey(const TypeKey&) = default;

		u64 hash() const;
		const auto& id() const { return _id; }

		friend bool operator==(const TypeKey& left, const TypeKey& right);
	};
}

namespace std
{
	template <>
	struct hash<parka::TypeKey>
	{
		parka::usize operator()(const parka::TypeKey& key) const;
	};
}


#endif
