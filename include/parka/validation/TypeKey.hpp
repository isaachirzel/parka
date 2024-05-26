#ifndef PARKA_VALIDATION_TYPE_KEY_HPP
#define PARKA_VALIDATION_TYPE_KEY_HPP

#include "parka/ir/TypeIr.hpp"

namespace parka::validation
{
	class TypeKey
	{
		const ir::TypeIr* _typeBase;

	public:

		TypeKey(const ir::TypeIr& typeBase);
		TypeKey(TypeKey&&) = default;
		TypeKey(const TypeKey&) = default;

		bool operator==(const TypeKey& other);

		friend struct std::hash<parka::validation::TypeKey>;
	};
}

template <>
struct std::hash<parka::validation::TypeKey>
{
	size_t operator()(const parka::validation::TypeKey& key) const;
};

#endif
