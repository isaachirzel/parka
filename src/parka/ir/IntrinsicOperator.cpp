#include "parka/ir/IntrinsicOperatorIr.hpp"
#include "parka/enum/OperatorType.hpp"
#include "parka/util/Float.hpp"

namespace parka::ir
{
	template <typename Left, typename Right, typename Return>
	IntrinsicOperatorIr op(OperatorType operatorType)
	{
		const auto& left = ir::Type::of<Left>();
		const auto& right = ir::Type::of<Right>();
		const auto& ret = ir::Type::of<Return>();

		return IntrinsicOperatorIr(operatorType, left, right, ret);
	}

	template <typename Left, typename Right = Left, typename Return = Left>
	IntrinsicOperatorIr add()
	{
		return op<Left, Right, Return>(OperatorType::Add);
	}

	template <typename Left, typename Right = Left, typename Return = Left>
	IntrinsicOperatorIr subtract()
	{
		return op<Left, Right, Return>(OperatorType::Subtract);
	}

	template <typename Left, typename Right = Left, typename Return = Left>
	IntrinsicOperatorIr multiply()
	{
		return op<Left, Right, Return>(OperatorType::Multiply);
	}

	template <typename Left, typename Right = Left, typename Return = Left>
	IntrinsicOperatorIr divide()
	{
		return op<Left, Right, Return>(OperatorType::Divide);
	}

	IntrinsicOperatorIr IntrinsicOperatorIr::entries[] =
	{
		add<Integer>(),
		subtract<Integer>(),
		multiply<Integer>(),
		divide<Integer>(),

		add<Float>(),
		subtract<Float>(),
		multiply<Float>(),
		divide<Float>(),

		add<u8>(),
		subtract<u8>(),
		multiply<u8>(),
		divide<u8>(),
		add<u8, Integer>(),
		subtract<u8, Integer>(),
		multiply<u8, Integer>(),
		divide<u8, Integer>(),

		add<u16>(),
		subtract<u16>(),
		multiply<u16>(),
		divide<u16>(),
		add<u16, Integer>(),
		subtract<u16, Integer>(),
		multiply<u16, Integer>(),
		divide<u16, Integer>(),

		add<u32>(),
		subtract<u32>(),
		multiply<u32>(),
		divide<u32>(),
		add<u32, Integer>(),
		subtract<u32, Integer>(),
		multiply<u32, Integer>(),
		divide<u32, Integer>(),

		add<u64>(),
		subtract<u64>(),
		multiply<u64>(),
		divide<u64>(),
		add<u64, Integer>(),
		subtract<u64, Integer>(),
		multiply<u64, Integer>(),
		divide<u64, Integer>(),

		add<i8>(),
		subtract<i8>(),
		multiply<i8>(),
		divide<i8>(),
		add<i8, Integer>(),
		subtract<i8, Integer>(),
		multiply<i8, Integer>(),
		divide<i8, Integer>(),

		add<i16>(),
		subtract<i16>(),
		multiply<i16>(),
		divide<i16>(),
		add<i16, Integer>(),
		subtract<i16, Integer>(),
		multiply<i16, Integer>(),
		divide<i16, Integer>(),

		add<i32>(),
		subtract<i32>(),
		multiply<i32>(),
		divide<i32>(),
		add<i32, Integer>(),
		subtract<i32, Integer>(),
		multiply<i32, Integer>(),
		divide<i32, Integer>(),

		add<i64>(),
		subtract<i64>(),
		multiply<i64>(),
		divide<i64>(),
		add<i64, Integer>(),
		subtract<i64, Integer>(),
		multiply<i64, Integer>(),
		divide<i64, Integer>(),

		add<f32>(),
		subtract<f32>(),
		multiply<f32>(),
		divide<f32>(),
		add<f32, Float>(),
		subtract<f32, Float>(),
		multiply<f32, Float>(),
		divide<f32, Float>(),

		add<f64>(),
		subtract<f64>(),
		multiply<f64>(),
		divide<f64>(),
		add<f64, Float>(),
		subtract<f64, Float>(),
		multiply<f64, Float>(),
		divide<f64, Float>(),
	};
	const usize IntrinsicOperatorIr::entryCount = sizeof(entries) / sizeof(*entries);

	IntrinsicOperatorIr::IntrinsicOperatorIr(OperatorType operatorType, const Type& type, const Type& returnType):
		OperatorIr(true),
		_lhs(type),
		_rhs(nullptr),
		_returnType(returnType),
		_operatorType(operatorType)
	{}

	IntrinsicOperatorIr::IntrinsicOperatorIr(OperatorType operatorType, const Type& lhs, const Type& rhs, const Type& returnType):
		OperatorIr(true),
		_lhs(lhs),
		_rhs(&rhs),
		_returnType(returnType),
		_operatorType(operatorType)
	{}
}
