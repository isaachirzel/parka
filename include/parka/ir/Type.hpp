#ifndef PARKA_IR_TYPE_HPP
#define PARKA_IR_TYPE_HPP

#include "parka/ir/TypeBase.hpp"

namespace parka::ir
{
	class Type
	{
	private:
	
		const TypeBase *_typeBase;
		// TODO: Add pointer info
		// TODO: Add Literal as typename for better type inference?
		
	public:

		static const Type packageType;
		static const Type functionType;
		static const Type typeNameType;
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

		Type(const TypeBase& base);
		Type(Type&&);
		Type(const Type&);
		~Type();

		const auto& typeBase() const { return _typeBase; }

		Type& operator=(Type&&);
		Type& operator=(const Type&);

		friend bool operator==(const Type& left, const Type& right);
		friend bool operator!=(const Type& left, const Type& right);
		friend std::ostream& operator<<(std::ostream& out, const Type& type);
	};
}

#endif
