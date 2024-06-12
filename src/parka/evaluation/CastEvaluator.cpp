#include "parka/evaluation/CastEvaluator.hpp"
#include "parka/ir/PrimitiveIr.hpp"
#include "parka/log/Log.hpp"
#include "parka/util/Float.hpp"
#include "parka/util/Integer.hpp"

namespace parka::evaluation
{
	template <typename To, typename From>
	Value& evaluateIntrinsicCast(Value& to, Value& from)
	{
		auto result = (To)from.getValue<From>();

		to.setValue<To>(result);

		return to;
	}

	template <typename To>
	Value& evaluateIntrinsicIntegerCast(Value& to, Value& from)
	{
		const auto& f = static_cast<const ir::PrimitiveIr&>(from.type());

		if (f.primitiveType() != PrimitiveType::Integer)
			log::fatal("Unable to evaluate cast `($)$`.", to.type(), from.type());

		return evaluateIntrinsicCast<To, Integer>(to, from);
	}

	template <typename To>
	Value& evaluateIntrinsicFloatCast(Value& to, Value& from)
	{
		const auto& f = static_cast<const ir::PrimitiveIr&>(from.type());

		if (f.primitiveType() != PrimitiveType::Float)
			log::fatal("Unable to evaluate cast `($)$`.", to.type(), from.type());

		return evaluateIntrinsicCast<To, Float>(to, from);
	}

	Value& evaluateIntrinsicCast(Value& to, Value& from)
	{
		const auto& t = static_cast<const ir::PrimitiveIr&>(to.type());

		switch (t.primitiveType())
		{
			case PrimitiveType::I8:
				return evaluateIntrinsicIntegerCast<i8>(to, from);
				
			case PrimitiveType::I16:
				return evaluateIntrinsicIntegerCast<i16>(to, from);

			case PrimitiveType::I32:
				return evaluateIntrinsicIntegerCast<i32>(to, from);

			case PrimitiveType::I64:
				return evaluateIntrinsicIntegerCast<i64>(to, from);

			case PrimitiveType::U8:
				return evaluateIntrinsicIntegerCast<u8>(to, from);

			case PrimitiveType::U16:
				return evaluateIntrinsicIntegerCast<u16>(to, from);

			case PrimitiveType::U32:
				return evaluateIntrinsicIntegerCast<u32>(to, from);

			case PrimitiveType::U64:
				return evaluateIntrinsicIntegerCast<u64>(to, from);

			case PrimitiveType::F32:
				return evaluateIntrinsicFloatCast<f32>(to, from);

			case PrimitiveType::F64:
				return evaluateIntrinsicFloatCast<f64>(to, from);

			default:
				break;
		}
		
		log::fatal("Unable to evaluate cast `($)$`.", to.type(), from.type());
	}

	Value& evaluateCast(const ir::CastIr&, Value& to, Value& from, LocalState&)
	{
		return evaluateIntrinsicCast(to, from);
	}
}
