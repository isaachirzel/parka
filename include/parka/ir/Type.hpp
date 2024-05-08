#ifndef PARKA_IR_TYPE_HPP
#define PARKA_IR_TYPE_HPP

#include "parka/ir/TypeBase.hpp"
#include "parka/util/Float.hpp"
#include "parka/util/Integer.hpp"

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
		static const Type integerType;
		static const Type floatType;
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

		template <typename T>
		static constexpr const ir::Type& of()
		{
			if constexpr (std::is_same_v<T, Integer>)
				return integerType;

			if constexpr (std::is_same_v<T, Float>)
				return floatType;

			if constexpr (std::is_same_v<T, void>)
				return voidType;

			if constexpr (std::is_same_v<T, u8>)
				return u8Type;

			if constexpr (std::is_same_v<T, u16>)
				return u16Type;

			if constexpr (std::is_same_v<T, u32>)
				return u32Type;

			if constexpr (std::is_same_v<T, u64>)
				return u64Type;

			if constexpr (std::is_same_v<T, i8>)
				return i8Type;

			if constexpr (std::is_same_v<T, i16>)
				return i16Type;

			if constexpr (std::is_same_v<T, i32>)
				return i32Type;

			if constexpr (std::is_same_v<T, i64>)
				return i64Type;

			if constexpr (std::is_same_v<T, f32>)
				return f32Type;

			if constexpr (std::is_same_v<T, f64>)
				return f64Type;

			if constexpr (std::is_same_v<T, bool>)
				return boolType;

			if constexpr (std::is_same_v<T, char>)
				return charType;
		}

		const auto& typeBase() const { return _typeBase; }

		Type& operator=(Type&&);
		Type& operator=(const Type&);

		friend bool operator==(const Type& left, const Type& right);
		friend bool operator!=(const Type& left, const Type& right);
		friend std::ostream& operator<<(std::ostream& out, const Type& type);
	};
}

#endif
