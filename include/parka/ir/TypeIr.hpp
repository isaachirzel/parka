#ifndef PARKA_IR_TYPE_HPP
#define PARKA_IR_TYPE_HPP

#include "parka/ir/TypeBaseIr.hpp"
#include "parka/util/Float.hpp"
#include "parka/util/Integer.hpp"
#include "parka/util/Set.hpp"


// ConstPtrTypeBase?
// MutPtrTypeBase?

namespace parka::ir
{
	class TypeIr
	{
		const TypeBaseIr& _typeBase;

	private:

		static Set<TypeIr> _typeIrs;

	public:

		static const TypeIr& packageType;
		static const TypeIr& functionType;
		static const TypeIr& typeNameType;
		static const TypeIr& voidType;
		static const TypeIr& integerType;
		static const TypeIr& floatType;
		static const TypeIr& u8Type;
		static const TypeIr& u16Type;
		static const TypeIr& u32Type;
		static const TypeIr& u64Type;
		static const TypeIr& i8Type;
		static const TypeIr& i16Type;
		static const TypeIr& i32Type;
		static const TypeIr& i64Type;
		static const TypeIr& f32Type;
		static const TypeIr& f64Type;
		static const TypeIr& boolType;
		static const TypeIr& charType;
		static const TypeIr& stringType;
	
	private:

		TypeIr(const TypeBaseIr& base);
		TypeIr(TypeIr&&) = default;
		TypeIr(const TypeIr&) = default;

	public:

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

			throw std::runtime_error("Invalid type.");
		}

		static const TypeIr& of(const TypeBaseIr& typeBase);

	public:

		const auto& typeBase() const { return _typeBase; }

		bool operator==(const TypeIr& other) const;
		bool operator!=(const TypeIr& other) const;

		friend std::ostream& operator<<(std::ostream& out, const TypeIr& type);

		friend struct std::hash<TypeIr>;
		friend class Set<TypeIr>;
	};
}

template <>
struct std::hash<parka::ir::TypeIr>
{
	std::size_t operator()(const parka::ir::TypeIr& type) const;
};

#endif
