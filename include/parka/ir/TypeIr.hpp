#ifndef PARKA_IR_TYPE_HPP
#define PARKA_IR_TYPE_HPP

#include "parka/ir/TypeBaseIr.hpp"
#include "parka/util/Float.hpp"
#include "parka/util/Integer.hpp"

namespace parka::ir
{
	class TypeIr
	{
		const TypeBaseIr* _typeBase;
		// TODO: Add pointer info
		// TODO: Add Literal as typename for better type inference?
		
	public:

		static const TypeIr packageType;
		static const TypeIr functionType;
		static const TypeIr typeNameType;
		static const TypeIr voidType;
		static const TypeIr integerType;
		static const TypeIr floatType;
		static const TypeIr u8Type;
		static const TypeIr u16Type;
		static const TypeIr u32Type;
		static const TypeIr u64Type;
		static const TypeIr i8Type;
		static const TypeIr i16Type;
		static const TypeIr i32Type;
		static const TypeIr i64Type;
		static const TypeIr f32Type;
		static const TypeIr f64Type;
		static const TypeIr boolType;
		static const TypeIr charType;
		static const TypeIr stringType;
		
	public:

		TypeIr();
		TypeIr(const TypeBaseIr& base);
		TypeIr(TypeIr&&);
		TypeIr(const TypeIr&);
		~TypeIr();

		template <typename T>
		static constexpr const ir::TypeIr& of()
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

		TypeIr& operator=(TypeIr&&);
		TypeIr& operator=(const TypeIr&);

		friend bool operator==(const TypeIr& left, const TypeIr& right);
		friend bool operator!=(const TypeIr& left, const TypeIr& right);
		friend std::ostream& operator<<(std::ostream& out, const TypeIr& type);

		friend struct std::hash<TypeIr>;
	};

}

template <>
struct std::hash<parka::ir::TypeIr>
{
	std::size_t operator()(const parka::ir::TypeIr& type) const
	{
		size_t h = (size_t)type._typeBase;

		h ^= h >> 33;
		h *= 0xff51afd7ed558ccdL;
		h ^= h >> 33;
		h *= 0xc4ceb9fe1a85ec53L;
		h ^= h >> 33;

		return h;
	}
};

#endif
