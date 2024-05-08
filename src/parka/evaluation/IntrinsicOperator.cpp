#include "parka/evaluation/IntrinsicOperators.hpp"
#include <type_traits>

namespace parka::evaluation
{
	template <typename Left, typename Right, std::conditional_t<(sizeof(Left) >= sizeof(Right)), Left, Right>(*operation)(Left, Right)>
	Value& op(Value& left, Value& right, State& state)
	{
		using Return = std::conditional_t<sizeof(Left) >= sizeof(Right), Left, Right>;

		const Left l = *(const Left*)left.value();
		const Right r = *(const Right*)right.value();
		const Return ret = operation(l, r);
		const ir::Type& valueType = ir::Type::of<Return>();
		Value& result = state.push(valueType);

		result.set((const byte*)&ret, sizeof(ret));

		return result;
	}

	template <typename Left, typename Right, typename Return = std::conditional_t<sizeof(Left) >= sizeof(Right), Left, Right>>
	inline Return _add(Left l, Right r)
	{
		return l + r;
	}

	template <typename Left, typename Right, typename Return = std::conditional_t<sizeof(Left) >= sizeof(Right), Left, Right>>
	inline Return _subtract(Left l, Right r)
	{
		return l - r;
	}

	template <typename Left, typename Right, typename Return = std::conditional_t<sizeof(Left) >= sizeof(Right), Left, Right>>
	inline Return _multiply(Left l, Right r)
	{
		return l * r;
	}

	template <typename Left, typename Right, typename Return = std::conditional_t<sizeof(Left) >= sizeof(Right), Left, Right>>
	inline Return _divide(Left l, Right r)
	{
		return l / r;
	}

	template <typename Left, typename Right>
	IntrinsicOperator add()
	{
		return op<Left, Right, _add>;
	}

	template <typename Left, typename Right>
	IntrinsicOperator subtract()
	{
		return op<Left, Right, _subtract>;
	}

	template <typename Left, typename Right>
	IntrinsicOperator multiply()
	{
		return op<Left, Right, _multiply>;
	}

	template <typename Left, typename Right>
	IntrinsicOperator divide()
	{
		return op<Left, Right, _divide>;
	}

	IntrinsicOperator intrinsicOperators[] = {
		add<u8, u8>(),
		subtract<u8, u8>(),
		multiply<u8, u8>(),
		divide<u8, u8>(),

		add<u16, u16>(),
		subtract<u16, u16>(),
		multiply<u16, u16>(),
		divide<u16, u16>(),

		add<u32, u32>(),
		subtract<u32, u32>(),
		multiply<u32, u32>(),
		divide<u32, u32>(),

		add<u64, u64>(),
		subtract<u64, u64>(),
		multiply<u64, u64>(),
		divide<u64, u64>(),

		add<f32, f32>(),
		subtract<f32, f32>(),
		multiply<f32, f32>(),
		divide<f32, f32>(),

		add<f64, f64>(),
		subtract<f64, f64>(),
		multiply<f64, f64>(),
		divide<f64, f64>(),
	};
	const usize IntrinsicOperatorCount = sizeof(intrinsicOperators) / sizeof(*intrinsicOperators);
}
