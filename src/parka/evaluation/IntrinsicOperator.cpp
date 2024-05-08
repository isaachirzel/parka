#include "parka/evaluation/IntrinsicOperators.hpp"

namespace parka::evaluation
{
	template <typename Left, typename Right, typename Return, const ir::Type& returnType>
	Value& add(Value& left, Value& right, State& state)
	{
		Left l = *(const Left*)left.value();
		Right r = *(const Right*)right.value();
		Return ret = l + r;
		Value& result = state.push(returnType);

		result.set((const byte*)&ret, sizeof(ret));

		return result;
	}

	template <typename Left, typename Right, typename Return, const ir::Type& returnType>
	Value& subtract(Value& left, Value& right, State& state)
	{
		Left l = *(const Left*)left.value();
		Right r = *(const Right*)right.value();
		Return ret = l - r;
		Value& result = state.push(returnType);

		result.set((const byte*)&ret, sizeof(ret));

		return result;
	}

	template <typename Left, typename Right, typename Return, const ir::Type& returnType>
	Value& multiply(Value& left, Value& right, State& state)
	{
		Left l = *(const Left*)left.value();
		Right r = *(const Right*)right.value();
		Return ret = l * r;
		Value& result = state.push(returnType);

		result.set((const byte*)&ret, sizeof(ret));

		return result;
	}

	template <typename Left, typename Right, typename Return, const ir::Type& returnType>
	Value& divide(Value& left, Value& right, State& state)
	{
		Left l = *(const Left*)left.value();
		Right r = *(const Right*)right.value();
		Return ret = l / r;
		Value& result = state.push(returnType);

		result.set((const byte*)&ret, sizeof(ret));

		return result;
	}

	template <typename Left, typename Right, typename Return, const ir::Type& returnType>
	Value& convert(Value& left, Value& right, State&)
	{
		left = right;
		
		return left;
	}

	IntrinsicOperator intrinsicOperators[] = {
		add<u8, u8, u8, ir::Type::u8Type>,
		subtract<u8, u8, u8, ir::Type::u8Type>,
		multiply<u8, u8, u8, ir::Type::u8Type>,
		divide<u8, u8, u8, ir::Type::u8Type>,
		// add<u16, u16, u16, ir::Type::u16Type>,
		// add<u32, u32, u32, ir::Type::u32Type>,
		// add<u64, u64, u64, ir::Type::u64Type>,
		// add<i8, i8, i8, ir::Type::i8Type>,
		// add<i16, i16, i16, ir::Type::i16Type>,
		// add<i32, i32, i32, ir::Type::i32Type>,
		// add<i64, i64, i64, ir::Type::i64Type>,
		// add<f32, f32, f32, ir::Type::f32Type>,
		// add<f64, f64, f64, ir::Type::f64Type>,
	};
	const usize IntrinsicOperatorCount = sizeof(intrinsicOperators) / sizeof(*intrinsicOperators);
}
