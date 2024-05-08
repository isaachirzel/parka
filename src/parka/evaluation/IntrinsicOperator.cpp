#include "parka/evaluation/IntrinsicOperators.hpp"
#include "parka/util/Print.hpp"

namespace parka::evaluation
{
	template <typename L, typename R, typename Ret, const ir::Type& retType>
	Value& add(Value& left, Value& right, State& state)
	{
		L l = *(const L*)left.value();
		R r = *(const R*)right.value();
		Ret ret = l + r;
		auto& result = state.push(retType);

		result.set((const byte*)&ret, sizeof(ret));

		return result;
	}

	IntrinsicOperator intrinsicOperators[] = {
		add<u8, u8, u8, ir::Type::u8Type>,
		add<u16, u16, u16, ir::Type::u16Type>,
		add<u32, u32, u32, ir::Type::u32Type>,
		add<u64, u64, u64, ir::Type::u64Type>,
		add<i8, i8, i8, ir::Type::i8Type>,
		add<i16, i16, i16, ir::Type::i16Type>,
		add<i32, i32, i32, ir::Type::i32Type>,
		add<i64, i64, i64, ir::Type::i64Type>,
		add<f32, f32, f32, ir::Type::f32Type>,
		add<f64, f64, f64, ir::Type::f64Type>,
	};
	const usize IntrinsicOperatorCount = sizeof(intrinsicOperators) / sizeof(*intrinsicOperators);
}
