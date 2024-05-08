#include "parka/evaluation/IntrinsicOperators.hpp"
#include "parka/ir/IntegerLiteral.hpp"
#include <type_traits>

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

	template <typename Left, typename Right, std::conditional_t<(sizeof(Left) >= sizeof(Right)), Left, Right>(*operation)(Left, Right)>
	Value& primitivesOp(Value& left, Value& right, State& state)
	{
		using Return = std::conditional_t<sizeof(Left) >= sizeof(Right), Left, Right>;

		return op<Left, Right, Return, ir::Type::of<Return>(), operation>(left, right, state);
	}

	template <typename Left, typename Right, typename Return = std::conditional_t<sizeof(Left) >= sizeof(Right), Left, Right>>
	inline Return _add(Left l, Right r)
	{
		return (Return)l + (Return)r;
	}

	template <typename Left, typename Right, typename Return = std::conditional_t<sizeof(Left) >= sizeof(Right), Left, Right>>
	inline Return _subtract(Left l, Right r)
	{
		return (Return)l - (Return)r;
	}

	template <typename Left, typename Right, typename Return = std::conditional_t<sizeof(Left) >= sizeof(Right), Left, Right>>
	inline Return _multiply(Left l, Right r)
	{
		return (Return)l * (Return)r;
	}

	template <typename Left, typename Right, typename Return = std::conditional_t<sizeof(Left) >= sizeof(Right), Left, Right>>
	inline Return _divide(Left l, Right r)
	{
		return (Return)l / (Return)r;
	}

	template <typename Left, typename Right>
	IntrinsicOperator add()
	{
		return primitivesOp<Left, Right, _add>;
	}

	template <typename Left, typename Right>
	IntrinsicOperator subtract()
	{
		return primitivesOp<Left, Right, _subtract>;
	}

	template <typename Left, typename Right>
	IntrinsicOperator multiply()
	{
		return primitivesOp<Left, Right, _multiply>;
	}

	template <typename Left, typename Right>
	IntrinsicOperator divide()
	{
		return primitivesOp<Left, Right, _divide>;
	}

	IntrinsicOperator addIntToInt()
	{
		return op<i64, i64, i64, ir::Type::integerLiteralType, _add>;
	}

	IntrinsicOperator subtractIntFromInt()
	{
		return op<i64, i64, i64, ir::Type::integerLiteralType, _subtract>;
	}

	IntrinsicOperator multiplyIntAndInt()
	{
		return op<i64, i64, i64, ir::Type::integerLiteralType, _multiply>;
	}

	IntrinsicOperator divideIntByInt()
	{
		return op<i64, i64, i64, ir::Type::integerLiteralType, _divide>;
	}

	IntrinsicOperator intrinsicOperators[] = {
		addIntToInt(),
		subtractIntFromInt(),
		multiplyIntAndInt(),
		divideIntByInt(),

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
	const usize intrinsicOperatorCount = sizeof(intrinsicOperators) / sizeof(*intrinsicOperators);
}
