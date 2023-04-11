#ifndef PARKA_TYPE_HPP
#define PARKA_TYPE_HPP

#include "parka/data/EntityId.hpp"
#include "parka/util/Primitives.hpp"
#include "parka/util/String.hpp"

namespace parka
{
	class Type
	{
	public:

		static const Type voidType;
		static const Type u8Type;
		static const Type u16Type;
		static const Type u32Type;
		static const Type u64Type;
		static const Type i8Type;
		static const Type i16Type;
		static const Type i32Type;
		static const Type i64Type;
		static const Type f32Type;
		static const Type f64Type;
		static const Type boolType;
		static const Type charType;
		static const Type stringType;

	private:

		EntityId _entityId;

		// TODO: Add pointer info
		// TODO: Add LiteralSyntax for better type inference?
	public:

		Type(EntityId entityId) :
		_entityId(entityId)
		{}
		Type(Type&&) = default;
		Type(const Type&) = default;
		~Type() = default;

		String getName() const;
		bool canConvertTo(const Type& other);

		const auto& entityId() const { return _entityId; }

		friend std::ostream& operator<<(std::ostream& out, const Type& type);

	};
}

#endif