#ifndef PARKA_TYPE_VALUE_TYPE_HPP
#define PARKA_TYPE_VALUE_TYPE_HPP

#include "parka/repository/EntityContext.hpp"
#include "parka/symbol/SymbolTable.hpp"
#include "parka/util/Common.hpp"
#include "parka/util/Optional.hpp"
#include "parka/util/String.hpp"

namespace parka
{
	class ValueType
	{
	private:

		EntityContext& _entity;
		// TODO: Add pointer info
		// TODO: Add LiteralSyntax for better type inference?

	public:

		static ValueType voidType;
		static ValueType u8Type;
		static ValueType u16Type;
		static ValueType u32Type;
		static ValueType u64Type;
		static ValueType i8Type;
		static ValueType i16Type;
		static ValueType i32Type;
		static ValueType i64Type;
		static ValueType f32Type;
		static ValueType f64Type;
		static ValueType boolType;
		static ValueType charType;
		static ValueType stringType;
		
	public:

		ValueType(EntityContext& entity);
		ValueType(ValueType&&) = default;
		ValueType(const ValueType&) = default;

		bool canConvertTo(const ValueType& other);

		const auto& entityId() const { return _entity; }

		friend std::ostream& operator<<(std::ostream& out, const ValueType& type);

	};
}

#endif