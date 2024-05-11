#include "parka/evaluation/IntrinsicOperator.hpp"
#include "parka/util/Float.hpp"
#include "parka/util/Integer.hpp"
#include <cstring>

namespace parka::evaluation
{
	template <typename Left, typename Right, typename Return, Return(*operation)(const Left&, const Right&)>
	Value& op(Value& left, Value& right, State& state)
	{
		const Left l = *(const Left*)left.value();
		const Right r = *(const Right*)right.value();
		const Return ret = operation(l, r);
		const auto& valueType = ir::Type::of<Return>();
		Value& result = state.push(valueType);
		byte buffer[sizeof(u64)] = { 0 };

		std::memcpy(buffer, &ret, sizeof(ret));
		result.setValue(buffer);

		return result;
	}

	template <typename Left, typename Right, typename Return>
	inline Return _add(const Left& l, const Right& r)
	{
		return l + r;
	}

	template <typename Left, typename Right, typename Return>
	inline Return _subtract(const Left& l, const Right& r)
	{
		return l - r;
	}

	template <typename Left, typename Right, typename Return>
	inline Return _multiply(const Left& l, const Right& r)
	{
		return l * r;
	}

	template <typename Left, typename Right, typename Return>
	inline Return _divide(const Left& l, const Right& r)
	{
		return l / r;
	}

	template <typename Left, typename Right = Left, typename Return = Left>
	IntrinsicOperator add()
	{
		return op<Left, Right, Return, _add<Left, Right, Return>>;
	}

	template <typename Left, typename Right = Left, typename Return = Left>
	IntrinsicOperator subtract()
	{
		return op<Left, Right, Return, _subtract>;
	}

	template <typename Left, typename Right = Left, typename Return = Left>
	IntrinsicOperator multiply()
	{
		return op<Left, Right, Return, _multiply>;
	}

	template <typename Left, typename Right = Left, typename Return = Left>
	IntrinsicOperator divide()
	{
		return op<Left, Right, Return, _divide>;
	}

	IntrinsicOperator intrinsicOperators[] =
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
	const usize intrinsicOperatorCount = sizeof(intrinsicOperators) / sizeof(*intrinsicOperators);
}
