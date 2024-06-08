#include "parka/evaluation/ConversionEvaluator.hpp"
#include "parka/ir/PrimitiveIr.hpp"
#include "parka/log/Log.hpp"
#include "parka/util/Float.hpp"
#include "parka/util/Integer.hpp"

namespace parka::evaluation
{
	template <typename To, typename From>
	Value& evaluateIntrinsicConversion(Value& to, Value& from)
	{
		auto result = (To)from.getValue<From>();

		to.setValue<To>(result);

		return to;
	}

	template <typename To>
	Value& evaluateIntrinsicIntegerConversion(Value& to, Value& from)
	{
		const auto& f = static_cast<const ir::PrimitiveIr&>(from.type());

		if (f.primitiveType() != PrimitiveType::Integer)
			log::fatal("Unable to evaluate conversion `($)$`.", to.type(), from.type());

		return evaluateIntrinsicConversion<To, Integer>(to, from);
	}

	template <typename To>
	Value& evaluateIntrinsicFloatConversion(Value& to, Value& from)
	{
		const auto& f = static_cast<const ir::PrimitiveIr&>(from.type());

		if (f.primitiveType() != PrimitiveType::Float)
			log::fatal("Unable to evaluate conversion `($)$`.", to.type(), from.type());

		return evaluateIntrinsicConversion<To, Float>(to, from);
	}

	Value& evaluateIntrinsicConversion(Value& to, Value& from)
	{
		const auto& t = static_cast<const ir::PrimitiveIr&>(to.type());

		switch (t.primitiveType())
		{
			case PrimitiveType::I8:
				return evaluateIntrinsicIntegerConversion<i8>(to, from);
				
			case PrimitiveType::I16:
				return evaluateIntrinsicIntegerConversion<i16>(to, from);

			case PrimitiveType::I32:
				return evaluateIntrinsicIntegerConversion<i32>(to, from);

			case PrimitiveType::I64:
				return evaluateIntrinsicIntegerConversion<i64>(to, from);

			case PrimitiveType::U8:
				return evaluateIntrinsicIntegerConversion<u8>(to, from);

			case PrimitiveType::U16:
				return evaluateIntrinsicIntegerConversion<u16>(to, from);

			case PrimitiveType::U32:
				return evaluateIntrinsicIntegerConversion<u32>(to, from);

			case PrimitiveType::U64:
				return evaluateIntrinsicIntegerConversion<u64>(to, from);

			case PrimitiveType::F32:
				return evaluateIntrinsicFloatConversion<f32>(to, from);

			case PrimitiveType::F64:
				return evaluateIntrinsicFloatConversion<f64>(to, from);

			default:
				break;
		}
		
		log::fatal("Unable to evaluate conversion `($)$`.", to.type(), from.type());
	}

	Value& evaluateConversion(const ir::ConversionIr&, Value& to, Value& from, LocalState&)
	{
		return evaluateIntrinsicConversion(to, from);
	}
}
