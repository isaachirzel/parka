#include "parka/evaluation/IntrinsicBinaryOperator.hpp"
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
	inline Return _bitwiseOr(const Left& l, const Right& r)
	{
		return l | r;
	}

	template <typename Left, typename Right, typename Return>
	inline Return _bitwiseXor(const Left& l, const Right& r)
	{
		return l ^ r;
	}

	template <typename Left, typename Right, typename Return>
	inline Return _bitwiseAnd(const Left& l, const Right& r)
	{
		return l & r;
	}

	template <typename Left, typename Right, typename Return>
	inline Return _leftShift(const Left& l, const Right& r)
	{
		return l << r;
	}

	template <typename Left, typename Right, typename Return>
	inline Return _rightShift(const Left& l, const Right& r)
	{
		return l >> r;
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

	template <typename Left, typename Right>
	inline bool _equals(const Left& l, const Right& r)
	{
		return l == r;
	}

	template <typename Left, typename Right>
	inline bool _notEquals(const Left& l, const Right& r)
	{
		return l != r;
	}

	inline bool _booleanOr(const bool& l, const bool& r)
	{
		return l || r;
	}

	inline bool _booleanAnd(const bool& l, const bool& r)
	{
		return l && r;
	}

	template <typename Left, typename Right = Left, typename Return = Left>
	IntrinsicBinaryOperator add()
	{
		return op<Left, Right, Return, _add<Left, Right, Return>>;
	}

	template <typename Left, typename Right = Left, typename Return = Left>
	IntrinsicBinaryOperator subtract()
	{
		return op<Left, Right, Return, _subtract>;
	}

	template <typename Left, typename Right = Left, typename Return = Left>
	IntrinsicBinaryOperator multiply()
	{
		return op<Left, Right, Return, _multiply>;
	}

	template <typename Left, typename Right = Left, typename Return = Left>
	IntrinsicBinaryOperator divide()
	{
		return op<Left, Right, Return, _divide>;
	}

	template <typename Left, typename Right = Left, typename Return = Left>
	IntrinsicBinaryOperator modulus()
	{
		return op<Left, Right, Return, _modulus>;
	}

	template <typename Left, typename Right = Left, typename Return = Left>
	IntrinsicBinaryOperator bitwiseOr()
	{
		return op<Left, Right, Return, _bitwiseOr>;
	}

	template <typename Left, typename Right = Left, typename Return = Left>
	IntrinsicBinaryOperator bitwiseXor()
	{
		return op<Left, Right, Return, _bitwiseXor>;
	}

	template <typename Left, typename Right = Left, typename Return = Left>
	IntrinsicBinaryOperator bitwiseAnd()
	{
		return op<Left, Right, Return, _bitwiseAnd>;
	}

	template <typename Left, typename Right = Left, typename Return = Left>
	IntrinsicBinaryOperator leftShift()
	{
		return op<Left, Right, Return, _leftShift>;
	}

	template <typename Left, typename Right = Left, typename Return = Left>
	IntrinsicBinaryOperator rightShift()
	{
		return op<Left, Right, Return, _rightShift>;
	}

	template <typename Left, typename Right = Left>
	IntrinsicBinaryOperator lessThan()
	{
		return op<Left, Right, bool, _lessThan>;
	}

	template <typename Left, typename Right = Left>
	IntrinsicBinaryOperator greaterThan()
	{
		return op<Left, Right, bool, _greaterThan>;
	}
	
	template <typename Left, typename Right = Left>
	IntrinsicBinaryOperator lessThanOrEqualTo()
	{
		return op<Left, Right, bool, _lessThanOrEqualTo>;
	}

	template <typename Left, typename Right = Left>
	IntrinsicBinaryOperator greaterThanOrEqualTo()
	{
		return op<Left, Right, bool, _greaterThanOrEqualTo>;
	}

	template <typename Left, typename Right = Left>
	IntrinsicBinaryOperator equals()
	{
		return op<Left, Right, bool, _equals>;
	}

	template <typename Left, typename Right = Left>
	IntrinsicBinaryOperator notEquals()
	{
		return op<Left, Right, bool, _notEquals>;
	}

	IntrinsicBinaryOperator booleanOr()
	{
		return op<bool, bool, bool, _booleanOr>;
	}

	IntrinsicBinaryOperator booleanAnd()
	{
		return op<bool, bool, bool, _booleanAnd>;
	}

	IntrinsicBinaryOperator intrinsicBinaryOperators[] =
	{
		add<Integer>(),
		subtract<Integer>(),
		multiply<Integer>(),
		divide<Integer>(),
		modulus<Integer>(),
		bitwiseOr<Integer>(),
		bitwiseXor<Integer>(),
		bitwiseAnd<Integer>(),
		leftShift<Integer>(),
		rightShift<Integer>(),
		lessThan<Integer>(),
		greaterThan<Integer>(),
		lessThanOrEqualTo<Integer>(),
		greaterThanOrEqualTo<Integer>(),
		equals<Integer>(),
		notEquals<Integer>(),

		add<u8>(),
		subtract<u8>(),
		multiply<u8>(),
		divide<u8>(),
		modulus<u8>(),
		bitwiseOr<u8>(),
		bitwiseXor<u8>(),
		bitwiseAnd<u8>(),
		leftShift<u8>(),
		rightShift<u8>(),
		lessThan<u8>(),
		greaterThan<u8>(),
		lessThanOrEqualTo<u8>(),
		greaterThanOrEqualTo<u8>(),
		equals<u8>(),
		notEquals<u8>(),
		
		add<u8, Integer>(),
		subtract<u8, Integer>(),
		multiply<u8, Integer>(),
		divide<u8, Integer>(),
		modulus<u8, Integer>(),
		bitwiseOr<u8, Integer>(),
		bitwiseXor<u8, Integer>(),
		bitwiseAnd<u8, Integer>(),
		leftShift<u8, Integer>(),
		rightShift<u8, Integer>(),
		lessThan<u8, Integer>(),
		greaterThan<u8, Integer>(),
		lessThanOrEqualTo<u8, Integer>(),
		greaterThanOrEqualTo<u8, Integer>(),
		equals<u8, Integer>(),
		notEquals<u8, Integer>(),

		add<u16>(),
		subtract<u16>(),
		multiply<u16>(),
		divide<u16>(),
		modulus<u16>(),
		bitwiseOr<u16>(),
		bitwiseXor<u16>(),
		bitwiseAnd<u16>(),
		leftShift<u16>(),
		rightShift<u16>(),
		lessThan<u16>(),
		greaterThan<u16>(),
		lessThanOrEqualTo<u16>(),
		greaterThanOrEqualTo<u16>(),
		equals<u16>(),
		notEquals<u16>(),

		add<u16, Integer>(),
		subtract<u16, Integer>(),
		multiply<u16, Integer>(),
		divide<u16, Integer>(),
		modulus<u16, Integer>(),
		bitwiseOr<u16, Integer>(),
		bitwiseXor<u16, Integer>(),
		bitwiseAnd<u16, Integer>(),
		leftShift<u16, Integer>(),
		rightShift<u16, Integer>(),
		lessThan<u16, Integer>(),
		greaterThan<u16, Integer>(),
		lessThanOrEqualTo<u16, Integer>(),
		greaterThanOrEqualTo<u16, Integer>(),
		equals<u16, Integer>(),
		notEquals<u16, Integer>(),

		add<u32>(),
		subtract<u32>(),
		multiply<u32>(),
		divide<u32>(),
		modulus<u32>(),
		bitwiseOr<u32>(),
		bitwiseXor<u32>(),
		bitwiseAnd<u32>(),
		leftShift<u32>(),
		rightShift<u32>(),
		lessThan<u32>(),
		greaterThan<u32>(),
		lessThanOrEqualTo<u32>(),
		greaterThanOrEqualTo<u32>(),
		equals<u32>(),
		notEquals<u32>(),

		add<u32, Integer>(),
		subtract<u32, Integer>(),
		multiply<u32, Integer>(),
		divide<u32, Integer>(),
		modulus<u32, Integer>(),
		bitwiseOr<u32, Integer>(),
		bitwiseXor<u32, Integer>(),
		bitwiseAnd<u32, Integer>(),
		leftShift<u32, Integer>(),
		rightShift<u32, Integer>(),
		lessThan<u32, Integer>(),
		greaterThan<u32, Integer>(),
		lessThanOrEqualTo<u32, Integer>(),
		greaterThanOrEqualTo<u32, Integer>(),
		equals<u32, Integer>(),
		notEquals<u32, Integer>(),

		add<u64>(),
		subtract<u64>(),
		multiply<u64>(),
		divide<u64>(),
		modulus<u64>(),
		bitwiseOr<u64>(),
		bitwiseXor<u64>(),
		bitwiseAnd<u64>(),
		leftShift<u64>(),
		rightShift<u64>(),
		lessThan<u64>(),
		greaterThan<u64>(),
		lessThanOrEqualTo<u64>(),
		greaterThanOrEqualTo<u64>(),
		equals<u64>(),
		notEquals<u64>(),

		add<u64, Integer>(),
		subtract<u64, Integer>(),
		multiply<u64, Integer>(),
		divide<u64, Integer>(),
		modulus<u64, Integer>(),
		bitwiseOr<u64, Integer>(),
		bitwiseXor<u64, Integer>(),
		bitwiseAnd<u64, Integer>(),
		leftShift<u64, Integer>(),
		rightShift<u64, Integer>(),
		lessThan<u64, Integer>(),
		greaterThan<u64, Integer>(),
		lessThanOrEqualTo<u64, Integer>(),
		greaterThanOrEqualTo<u64, Integer>(),
		equals<u64, Integer>(),
		notEquals<u64, Integer>(),

		add<i8>(),
		subtract<i8>(),
		multiply<i8>(),
		divide<i8>(),
		modulus<i8>(),
		bitwiseOr<i8>(),
		bitwiseXor<i8>(),
		bitwiseAnd<i8>(),
		leftShift<i8>(),
		rightShift<i8>(),
		lessThan<i8>(),
		greaterThan<i8>(),
		lessThanOrEqualTo<i8>(),
		greaterThanOrEqualTo<i8>(),
		equals<i8>(),
		notEquals<i8>(),

		add<i8, Integer>(),
		subtract<i8, Integer>(),
		multiply<i8, Integer>(),
		divide<i8, Integer>(),
		modulus<i8, Integer>(),
		bitwiseOr<i8, Integer>(),
		bitwiseXor<i8, Integer>(),
		bitwiseAnd<i8, Integer>(),
		leftShift<i8, Integer>(),
		rightShift<i8, Integer>(),
		lessThan<i8, Integer>(),
		greaterThan<i8, Integer>(),
		lessThanOrEqualTo<i8, Integer>(),
		greaterThanOrEqualTo<i8, Integer>(),
		equals<i8, Integer>(),
		notEquals<i8, Integer>(),

		add<i16>(),
		subtract<i16>(),
		multiply<i16>(),
		divide<i16>(),
		modulus<i16>(),
		bitwiseOr<i16>(),
		bitwiseXor<i16>(),
		bitwiseAnd<i16>(),
		leftShift<i16>(),
		rightShift<i16>(),
		lessThan<i16>(),
		greaterThan<i16>(),
		lessThanOrEqualTo<i16>(),
		greaterThanOrEqualTo<i16>(),
		equals<i16>(),
		notEquals<i16>(),

		add<i16, Integer>(),
		subtract<i16, Integer>(),
		multiply<i16, Integer>(),
		divide<i16, Integer>(),
		modulus<i16, Integer>(),
		bitwiseOr<i16, Integer>(),
		bitwiseXor<i16, Integer>(),
		bitwiseAnd<i16, Integer>(),
		leftShift<i16, Integer>(),
		rightShift<i16, Integer>(),
		lessThan<i16, Integer>(),
		greaterThan<i16, Integer>(),
		lessThanOrEqualTo<i16, Integer>(),
		greaterThanOrEqualTo<i16, Integer>(),
		equals<i16, Integer>(),
		notEquals<i16, Integer>(),

		add<i32>(),
		subtract<i32>(),
		multiply<i32>(),
		divide<i32>(),
		modulus<i32>(),
		bitwiseOr<i32>(),
		bitwiseXor<i32>(),
		bitwiseAnd<i32>(),
		leftShift<i32>(),
		rightShift<i32>(),
		lessThan<i32>(),
		greaterThan<i32>(),
		lessThanOrEqualTo<i32>(),
		greaterThanOrEqualTo<i32>(),
		equals<i32>(),
		notEquals<i32>(),

		add<i32, Integer>(),
		subtract<i32, Integer>(),
		multiply<i32, Integer>(),
		divide<i32, Integer>(),
		modulus<i32, Integer>(),
		bitwiseOr<i32, Integer>(),
		bitwiseXor<i32, Integer>(),
		bitwiseAnd<i32, Integer>(),
		leftShift<i32, Integer>(),
		rightShift<i32, Integer>(),
		lessThan<i32, Integer>(),
		greaterThan<i32, Integer>(),
		lessThanOrEqualTo<i32, Integer>(),
		greaterThanOrEqualTo<i32, Integer>(),
		equals<i32, Integer>(),
		notEquals<i32, Integer>(),

		add<i64>(),
		subtract<i64>(),
		multiply<i64>(),
		divide<i64>(),
		modulus<i64>(),
		bitwiseOr<i64>(),
		bitwiseXor<i64>(),
		bitwiseAnd<i64>(),
		leftShift<i64>(),
		rightShift<i64>(),
		lessThan<i64>(),
		greaterThan<i64>(),
		lessThanOrEqualTo<i64>(),
		greaterThanOrEqualTo<i64>(),
		equals<i64>(),
		notEquals<i64>(),
		
		add<i64, Integer>(),
		subtract<i64, Integer>(),
		multiply<i64, Integer>(),
		divide<i64, Integer>(),
		modulus<i64, Integer>(),
		bitwiseOr<i64, Integer>(),
		bitwiseXor<i64, Integer>(),
		bitwiseAnd<i64, Integer>(),
		leftShift<i64, Integer>(),
		rightShift<i64, Integer>(),
		lessThan<i64, Integer>(),
		greaterThan<i64, Integer>(),
		lessThanOrEqualTo<i64, Integer>(),
		greaterThanOrEqualTo<i64, Integer>(),
		equals<i64, Integer>(),
		notEquals<i64, Integer>(),

		add<Float>(),
		subtract<Float>(),
		multiply<Float>(),
		divide<Float>(),
		lessThan<Float>(),
		greaterThan<Float>(),
		lessThanOrEqualTo<Float>(),
		greaterThanOrEqualTo<Float>(),
		equals<Float>(),
		notEquals<Float>(),

		add<f32>(),
		subtract<f32>(),
		multiply<f32>(),
		divide<f32>(),
		lessThan<f32>(),
		greaterThan<f32>(),
		lessThanOrEqualTo<f32>(),
		greaterThanOrEqualTo<f32>(),
		equals<f32>(),
		notEquals<f32>(),

		add<f32, Float>(),
		subtract<f32, Float>(),
		multiply<f32, Float>(),
		divide<f32, Float>(),
		lessThan<f32, Float>(),
		greaterThan<f32, Float>(),
		lessThanOrEqualTo<f32, Float>(),
		greaterThanOrEqualTo<f32, Float>(),
		equals<f32, Float>(),
		notEquals<f32, Float>(),

		add<f64>(),
		subtract<f64>(),
		multiply<f64>(),
		divide<f64>(),
		lessThan<f64>(),
		greaterThan<f64>(),
		lessThanOrEqualTo<f64>(),
		greaterThanOrEqualTo<f64>(),
		equals<f64>(),
		notEquals<f64>(),

		add<f64, Float>(),
		subtract<f64, Float>(),
		multiply<f64, Float>(),
		divide<f64, Float>(),
		lessThan<f64, Float>(),
		greaterThan<f64, Float>(),
		lessThanOrEqualTo<f64, Float>(),
		greaterThanOrEqualTo<f64, Float>(),
		equals<f64, Float>(),
		notEquals<f64, Float>(),

		equals<bool>(),
		notEquals<bool>(),
		booleanAnd(),
		booleanOr(),

		equals<char>(),
		notEquals<char>(),
	};
	const usize intrinsicBinaryOperatorCount = sizeof(intrinsicBinaryOperators) / sizeof(intrinsicBinaryOperators[0]);
}
