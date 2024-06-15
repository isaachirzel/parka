#include "parka/evaluation/CastEvaluator.hpp"
#include "parka/ir/PrimitiveIr.hpp"
#include "parka/log/Log.hpp"
#include "parka/util/Float.hpp"
#include "parka/util/Integer.hpp"

namespace parka::evaluation
{
	template <typename From, typename To>
	Value& evaluateIntrinsicCast(Value& from, Value& to)
	{
		auto result = (To)from.getValue<From>();

		to.setValue<To>(result);

		return to;
	}

	template <typename From>
	Value& evaluateIntrinsicIntegerCast(Value& from, Value& to)
	{
		const auto& t = static_cast<const ir::PrimitiveIr&>(to.type());

		switch (t.primitiveType())
		{
			case PrimitiveType::U8:
				return evaluateIntrinsicCast<From, u8>(from, to);

			case PrimitiveType::U16:
				return evaluateIntrinsicCast<From, u16>(from, to);

			case PrimitiveType::U32:
				return evaluateIntrinsicCast<From, u32>(from, to);

			case PrimitiveType::U64:
				return evaluateIntrinsicCast<From, u64>(from, to);

			case PrimitiveType::I8:
				return evaluateIntrinsicCast<From, i8>(from, to);

			case PrimitiveType::I16:
				return evaluateIntrinsicCast<From, i16>(from, to);

			case PrimitiveType::I32:
				return evaluateIntrinsicCast<From, i32>(from, to);

			case PrimitiveType::I64:
				return evaluateIntrinsicCast<From, i64>(from, to);
			
			default:
				break;
		}

		abort();
	}

	template <typename From>
	Value& evaluateIntrinsicFloatCast(Value& from, Value& to)
	{
		const auto& t = static_cast<const ir::PrimitiveIr&>(to.type());

		switch (t.primitiveType())
		{
			case PrimitiveType::F32:
				return evaluateIntrinsicCast<From, f32>(from, to);

			case PrimitiveType::F64:
				return evaluateIntrinsicCast<From, f64>(from, to);

			default:
				break;
		}

		abort();
	}

	Value& evaluateIntrinsicCast(Value& from, Value& to)
	{
		const auto& f = static_cast<const ir::PrimitiveIr&>(from.type());

		switch (f.primitiveType())
		{
			case PrimitiveType::Integer:
				return evaluateIntrinsicIntegerCast<Integer>(from, to);

			case PrimitiveType::I8:
				return evaluateIntrinsicIntegerCast<i8>(from, to);
				
			case PrimitiveType::I16:
				return evaluateIntrinsicIntegerCast<i16>(from, to);

			case PrimitiveType::I32:
				return evaluateIntrinsicIntegerCast<i32>(from, to);

			case PrimitiveType::I64:
				return evaluateIntrinsicIntegerCast<i64>(from, to);

			case PrimitiveType::U8:
				return evaluateIntrinsicIntegerCast<u8>(from, to);

			case PrimitiveType::U16:
				return evaluateIntrinsicIntegerCast<u16>(from, to);

			case PrimitiveType::U32:
				return evaluateIntrinsicIntegerCast<u32>(from, to);

			case PrimitiveType::U64:
				return evaluateIntrinsicIntegerCast<u64>(from, to);

			case PrimitiveType::Float:
				return evaluateIntrinsicFloatCast<Float>(from, to);

			case PrimitiveType::F32:
				return evaluateIntrinsicFloatCast<f32>(from, to);

			case PrimitiveType::F64:
				return evaluateIntrinsicFloatCast<f64>(from, to);

			default:
				break;
		}
		
		abort();
	}

	Value& evaluateCast(const ir::CastIr&, Value& from, Value& to, LocalState&)
	{
		return evaluateIntrinsicCast(from, to);
	}
}
