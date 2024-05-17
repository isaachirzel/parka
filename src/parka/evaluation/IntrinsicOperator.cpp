#include "parka/evaluation/IntrinsicOperator.hpp"
#include "parka/util/Float.hpp"
#include "parka/util/Integer.hpp"
#include <cstring>

namespace parka::evaluation
{
	template <typename Left, typename Right, typename Return, Return(*operation)(const Left&, const Right&)>
	Value& op(Value& left, Value& right, LocalState& state)
	{
		const Left l = *(const Left*)left.value();
		const Right r = *(const Right*)right.value();
		const Return ret = operation(l, r);
		const auto& valueType = ir::TypeIr::of<Return>();
		auto& result = state.pushValue(valueType);

		result.setValue(ret);

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

	template <typename Left, typename Right, typename Return>
	inline Return _modulus(const Left& l, const Right& r)
	{
		return l % r;
	}

	template <typename Left, typename Right, typename Return>
	inline Return _lessThan(const Left& l, const Right& r)
	{
		return l < r;
	}

	template <typename Left, typename Right, typename Return>
	inline Return _greaterThan(const Left& l, const Right& r)
	{
		return l > r;
	}

	template <typename Left, typename Right, typename Return>
	inline Return _lessThanOrEqualTo(const Left& l, const Right& r)
	{
		return l <= r;
	}

	template <typename Left, typename Right, typename Return>
	inline Return _greaterThanOrEqualTo(const Left& l, const Right& r)
	{
		return l >= r;
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

	template <typename Left, typename Right = Left, typename Return = Left>
	IntrinsicOperator modulus()
	{
		return op<Left, Right, Return, _modulus>;
	}

	template <typename Left, typename Right = Left>
	IntrinsicOperator lessThan()
	{
		return op<Left, Right, bool, _lessThan>;
	}

	template <typename Left, typename Right = Left>
	IntrinsicOperator greaterThan()
	{
		return op<Left, Right, bool, _greaterThan>;
	}
	
	template <typename Left, typename Right = Left>
	IntrinsicOperator lessThanOrEqualTo()
	{
		return op<Left, Right, bool, _lessThanOrEqualTo>;
	}

	template <typename Left, typename Right = Left>
	IntrinsicOperator greaterThanOrEqualTo()
	{
		return op<Left, Right, bool, _greaterThanOrEqualTo>;
	}

	IntrinsicOperator intrinsicOperators[] =
	{
		add<Integer>(),
		subtract<Integer>(),
		multiply<Integer>(),
		divide<Integer>(),
		modulus<Integer>(),
		lessThan<Integer>(),
		greaterThan<Integer>(),
		lessThanOrEqualTo<Integer>(),
		greaterThanOrEqualTo<Integer>(),

		add<u8>(),
		subtract<u8>(),
		multiply<u8>(),
		divide<u8>(),
		modulus<u8>(),
		lessThan<u8>(),
		greaterThan<u8>(),
		lessThanOrEqualTo<u8>(),
		greaterThanOrEqualTo<u8>(),
		
		add<u8, Integer>(),
		subtract<u8, Integer>(),
		multiply<u8, Integer>(),
		divide<u8, Integer>(),
		modulus<u8, Integer>(),
		lessThan<u8, Integer>(),
		greaterThan<u8, Integer>(),
		lessThanOrEqualTo<u8, Integer>(),
		greaterThanOrEqualTo<u8, Integer>(),

		add<u16>(),
		subtract<u16>(),
		multiply<u16>(),
		divide<u16>(),
		modulus<u16>(),
		lessThan<u16>(),
		greaterThan<u16>(),
		lessThanOrEqualTo<u16>(),
		greaterThanOrEqualTo<u16>(),

		add<u16, Integer>(),
		subtract<u16, Integer>(),
		multiply<u16, Integer>(),
		divide<u16, Integer>(),
		modulus<u16, Integer>(),
		lessThan<u16, Integer>(),
		greaterThan<u16, Integer>(),
		lessThanOrEqualTo<u16, Integer>(),
		greaterThanOrEqualTo<u16, Integer>(),

		add<u32>(),
		subtract<u32>(),
		multiply<u32>(),
		divide<u32>(),
		modulus<u32>(),
		lessThan<u32>(),
		greaterThan<u32>(),
		lessThanOrEqualTo<u32>(),
		greaterThanOrEqualTo<u32>(),

		add<u32, Integer>(),
		subtract<u32, Integer>(),
		multiply<u32, Integer>(),
		divide<u32, Integer>(),
		modulus<u32, Integer>(),
		lessThan<u32, Integer>(),
		greaterThan<u32, Integer>(),
		lessThanOrEqualTo<u32, Integer>(),
		greaterThanOrEqualTo<u32, Integer>(),

		add<u64>(),
		subtract<u64>(),
		multiply<u64>(),
		divide<u64>(),
		modulus<u64>(),
		lessThan<u64>(),
		greaterThan<u64>(),
		lessThanOrEqualTo<u64>(),
		greaterThanOrEqualTo<u64>(),

		add<u64, Integer>(),
		subtract<u64, Integer>(),
		multiply<u64, Integer>(),
		divide<u64, Integer>(),
		modulus<u64, Integer>(),
		lessThan<u64, Integer>(),
		greaterThan<u64, Integer>(),
		lessThanOrEqualTo<u64, Integer>(),
		greaterThanOrEqualTo<u64, Integer>(),

		add<i8>(),
		subtract<i8>(),
		multiply<i8>(),
		divide<i8>(),
		modulus<i8>(),
		lessThan<i8>(),
		greaterThan<i8>(),
		lessThanOrEqualTo<i8>(),
		greaterThanOrEqualTo<i8>(),

		add<i8, Integer>(),
		subtract<i8, Integer>(),
		multiply<i8, Integer>(),
		divide<i8, Integer>(),
		modulus<i8, Integer>(),
		lessThan<i8, Integer>(),
		greaterThan<i8, Integer>(),
		lessThanOrEqualTo<i8, Integer>(),
		greaterThanOrEqualTo<i8, Integer>(),

		add<i16>(),
		subtract<i16>(),
		multiply<i16>(),
		divide<i16>(),
		modulus<i16>(),
		lessThan<i16>(),
		greaterThan<i16>(),
		lessThanOrEqualTo<i16>(),
		greaterThanOrEqualTo<i16>(),

		add<i16, Integer>(),
		subtract<i16, Integer>(),
		multiply<i16, Integer>(),
		divide<i16, Integer>(),
		modulus<i16, Integer>(),
		lessThan<i16, Integer>(),
		greaterThan<i16, Integer>(),
		lessThanOrEqualTo<i16, Integer>(),
		greaterThanOrEqualTo<i16, Integer>(),

		add<i32>(),
		subtract<i32>(),
		multiply<i32>(),
		divide<i32>(),
		modulus<i32>(),
		lessThan<i32>(),
		greaterThan<i32>(),
		lessThanOrEqualTo<i32>(),
		greaterThanOrEqualTo<i32>(),

		add<i32, Integer>(),
		subtract<i32, Integer>(),
		multiply<i32, Integer>(),
		divide<i32, Integer>(),
		modulus<i32, Integer>(),
		lessThan<i32, Integer>(),
		greaterThan<i32, Integer>(),
		lessThanOrEqualTo<i32, Integer>(),
		greaterThanOrEqualTo<i32, Integer>(),

		add<i64>(),
		subtract<i64>(),
		multiply<i64>(),
		divide<i64>(),
		modulus<i64>(),
		lessThan<i64>(),
		greaterThan<i64>(),
		lessThanOrEqualTo<i64>(),
		greaterThanOrEqualTo<i64>(),
		
		add<i64, Integer>(),
		subtract<i64, Integer>(),
		multiply<i64, Integer>(),
		divide<i64, Integer>(),
		modulus<i64, Integer>(),
		lessThan<i64, Integer>(),
		greaterThan<i64, Integer>(),
		lessThanOrEqualTo<i64, Integer>(),
		greaterThanOrEqualTo<i64, Integer>(),

		add<Float>(),
		subtract<Float>(),
		multiply<Float>(),
		divide<Float>(),
		lessThan<Integer>(),
		greaterThan<Integer>(),
		lessThanOrEqualTo<Integer>(),
		greaterThanOrEqualTo<Integer>(),

		add<f32>(),
		subtract<f32>(),
		multiply<f32>(),
		divide<f32>(),
		lessThan<f32>(),
		greaterThan<f32>(),
		lessThanOrEqualTo<f32>(),
		greaterThanOrEqualTo<f32>(),

		add<f32, Float>(),
		subtract<f32, Float>(),
		multiply<f32, Float>(),
		divide<f32, Float>(),
		lessThan<f32, Float>(),
		greaterThan<f32, Float>(),
		lessThanOrEqualTo<f32, Float>(),
		greaterThanOrEqualTo<f32, Float>(),

		add<f64>(),
		subtract<f64>(),
		multiply<f64>(),
		divide<f64>(),
		lessThan<f64>(),
		greaterThan<f64>(),
		lessThanOrEqualTo<f64>(),
		greaterThanOrEqualTo<f64>(),

		add<f64, Float>(),
		subtract<f64, Float>(),
		multiply<f64, Float>(),
		divide<f64, Float>(),
		lessThan<f64, Float>(),
		greaterThan<f64, Float>(),
		lessThanOrEqualTo<f64, Float>(),
		greaterThanOrEqualTo<f64, Float>(),
	};
	const usize intrinsicOperatorCount = sizeof(intrinsicOperators) / sizeof(*intrinsicOperators);
}
