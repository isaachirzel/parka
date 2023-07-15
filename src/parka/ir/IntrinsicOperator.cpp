#include "parka/ir/IntrinsicOperator.hpp"

namespace parka::ir
{
	const IntrinsicOperatorIr IntrinsicOperatorIr::entries[] =
	{
		// u8
		{ OperatorType::Add, { Type::u8Type, Type::u8Type }, Type::u8Type },
		{ OperatorType::Add, { Type::u8Type, Type::u16Type }, Type::u16Type },
		{ OperatorType::Add, { Type::u8Type, Type::u32Type }, Type::u32Type },
		{ OperatorType::Add, { Type::u8Type, Type::u64Type }, Type::u64Type },

		// u16
		{ OperatorType::Add, { Type::u16Type, Type::u8Type }, Type::u16Type },
		{ OperatorType::Add, { Type::u16Type, Type::u16Type }, Type::u16Type },
		{ OperatorType::Add, { Type::u16Type, Type::u32Type }, Type::u32Type },
		{ OperatorType::Add, { Type::u16Type, Type::u64Type }, Type::u64Type },

		// u32
		{ OperatorType::Add, { Type::u32Type, Type::u8Type }, Type::u32Type },
		{ OperatorType::Add, { Type::u32Type, Type::u16Type }, Type::u32Type },
		{ OperatorType::Add, { Type::u32Type, Type::u32Type }, Type::u32Type },
		{ OperatorType::Add, { Type::u32Type, Type::u64Type }, Type::u64Type },

		// u64
		{ OperatorType::Add, { Type::u64Type, Type::u8Type }, Type::u64Type },
		{ OperatorType::Add, { Type::u64Type, Type::u16Type }, Type::u64Type },
		{ OperatorType::Add, { Type::u64Type, Type::u32Type }, Type::u64Type },
		{ OperatorType::Add, { Type::u64Type, Type::u64Type }, Type::u64Type },

		// i8
		{ OperatorType::Add, { Type::i8Type, Type::i8Type }, Type::i8Type },
		{ OperatorType::Add, { Type::i8Type, Type::i16Type }, Type::i16Type },
		{ OperatorType::Add, { Type::i8Type, Type::i32Type }, Type::i32Type },
		{ OperatorType::Add, { Type::i8Type, Type::i64Type }, Type::i64Type },

		// i16
		{ OperatorType::Add, { Type::i16Type, Type::i8Type }, Type::i16Type },
		{ OperatorType::Add, { Type::i16Type, Type::i16Type }, Type::i16Type },
		{ OperatorType::Add, { Type::i16Type, Type::i32Type }, Type::i32Type },
		{ OperatorType::Add, { Type::i16Type, Type::i64Type }, Type::i64Type },

		// i32
		{ OperatorType::Add, { Type::i32Type, Type::i8Type }, Type::i32Type },
		{ OperatorType::Add, { Type::i32Type, Type::i16Type }, Type::i32Type },
		{ OperatorType::Add, { Type::i32Type, Type::i32Type }, Type::i32Type },
		{ OperatorType::Add, { Type::i32Type, Type::i64Type }, Type::i64Type },

		// i64
		{ OperatorType::Add, { Type::i64Type, Type::i8Type }, Type::i64Type },
		{ OperatorType::Add, { Type::i64Type, Type::i16Type }, Type::i64Type },
		{ OperatorType::Add, { Type::i64Type, Type::i32Type }, Type::i64Type },
		{ OperatorType::Add, { Type::i64Type, Type::i64Type }, Type::i64Type },

		{ OperatorType::Add, { Type::f32Type, Type::f32Type }, Type::f32Type },
		{ OperatorType::Add, { Type::f32Type, Type::f64Type }, Type::f64Type },

		{ OperatorType::Add, { Type::f64Type, Type::f32Type }, Type::f64Type },
		{ OperatorType::Add, { Type::f64Type, Type::f64Type }, Type::f64Type },
	};
	const usize IntrinsicOperatorIr::entryCount = sizeof(entries) / sizeof(*entries);

	IntrinsicOperatorIr::IntrinsicOperatorIr(OperatorType operatorType, Array<Type>&& types, const Type& returnType):
	OperatorIr(true),
	_types(std::move(types)),
	_returnType(returnType),
	_operatorType(operatorType)
	{}
}
