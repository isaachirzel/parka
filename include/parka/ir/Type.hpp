#ifndef PARKA_TYPE_VALUE_TYPE_HPP
#define PARKA_TYPE_VALUE_TYPE_HPP

#include "parka/ir/TypeBase.hpp"
#include "parka/util/Common.hpp"
#include "parka/util/Optional.hpp"
#include "parka/util/String.hpp"

namespace parka::ir
{
	class Type
	{
	private:
		TypeBase& _typeBase;
		// TODO: Add pointer info
		// TODO: Add Literal as typename for better type inference?
		
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
		
	public:

		Type(TypeBase& tn):
		_typeBase(tn)
		{}
		Type(Type&&) = default;
		Type(const Type&) = default;

		bool canConvertTo(const Type& other) const;
		const auto& typeBase() const { return _typeBase; }

		friend std::ostream& operator<<(std::ostream& out, const Type& type);
	};
}

#endif