#ifndef PARKA_SYNTAX_TYPE_TYPE_ID_SYNTAX_HPP
#define PARKA_SYNTAX_TYPE_TYPE_ID_SYNTAX_HPP

#include "parka/repository/EntitySyntaxId.hpp"
#include "parka/util/Common.hpp"

#include <cassert>

namespace parka
{
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

		const auto& type() const { return _type; }
		const auto& index() const { return _index; }

		friend bool operator==(const TypeId& left, const TypeId& right);
	};
}

namespace std
{
	template <>
	struct hash<parka::TypeId>
	{
		parka::usize operator()(const parka::TypeId& key) const;
	};
}

#endif