#ifndef PARKA_SYMBOL_TYPE_KEY_HPP
#define PARKA_SYMBOL_TYPE_KEY_HPP

#include "parka/ir/TypeBaseIr.hpp"

namespace parka
{
	class TypeKey
	{
		const ir::TypeBaseIr* _typeBase;

	public:

		TypeKey(const ir::TypeBaseIr& typeBase);
		TypeKey(TypeKey&&) = default;
		TypeKey(const TypeKey&) = default;

		bool operator==(const TypeKey& other);

		friend struct std::hash<parka::TypeKey>;
	};
}

template <>
struct std::hash<parka::TypeKey>
{
	size_t operator()(const parka::TypeKey& key) const;
};

#endif
