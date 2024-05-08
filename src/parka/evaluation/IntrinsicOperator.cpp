#include "parka/evaluation/IntrinsicOperators.hpp"
#include "parka/util/Float.hpp"
#include "parka/util/Integer.hpp"

namespace parka::evaluation
{
	template <typename Left, typename Right, typename Return, const ir::Type& valueType, Return(*operation)(Left, Right)>
	Value& op(Value& left, Value& right, State& state)
	{
		const Left l = *(const Left*)left.value();
		const Right r = *(const Right*)right.value();
		const Return ret = operation(l, r);
		Value& result = state.push(valueType);

		result.set((const byte*)&ret, sizeof(ret));

		return result;
	}

	template <typename T, T(*operation)(T, T)>
	Value& primitivesOp(Value& left, Value& right, State& state)
	{
		return op<T, T, T, ir::Type::of<T>(), operation>(left, right, state);
	}

	template <typename T>
	inline T _add(T l, T r)
	{
		return l + r;
	}

	template <typename T>
	inline T _subtract(T l, T r)
	{
		return l - r;
	}

	template <typename T>
	inline T _multiply(T l, T r)
	{
		return l * r;
	}

	template <typename T>
	inline T _divide(T l, T r)
	{
		return l / r;
	}

	template <typename T>
	IntrinsicOperator add()
	{
		return primitivesOp<T, _add>;
	}

	template <typename T>
	IntrinsicOperator subtract()
	{
		return primitivesOp<T, _subtract>;
	}

	template <typename T>
	IntrinsicOperator multiply()
	{
		return primitivesOp<T, _multiply>;
	}

	template <typename T>
	IntrinsicOperator divide()
	{
		return primitivesOp<T, _divide>;
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

		add<u16>(),
		subtract<u16>(),
		multiply<u16>(),
		divide<u16>(),

		add<u32>(),
		subtract<u32>(),
		multiply<u32>(),
		divide<u32>(),

		add<u64>(),
		subtract<u64>(),
		multiply<u64>(),
		divide<u64>(),

		add<i8>(),
		subtract<i8>(),
		multiply<i8>(),
		divide<i8>(),

		add<i16>(),
		subtract<i16>(),
		multiply<i16>(),
		divide<i16>(),

		add<i32>(),
		subtract<i32>(),
		multiply<i32>(),
		divide<i32>(),

		add<i64>(),
		subtract<i64>(),
		multiply<i64>(),
		divide<i64>(),

		add<f32>(),
		subtract<f32>(),
		multiply<f32>(),
		divide<f32>(),

		add<f64>(),
		subtract<f64>(),
		multiply<f64>(),
		divide<f64>()
	};
	const usize intrinsicOperatorCount = sizeof(intrinsicOperators) / sizeof(*intrinsicOperators);
}
