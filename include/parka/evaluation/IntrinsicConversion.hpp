#ifndef PARKA_EVALUATION_INTRINSIC_CONVERSIONS_HPP
#define PARKA_EVALUATION_INTRINSIC_CONVERSIONS_HPP

#include "parka/evaluation/Value.hpp"
#include "parka/validation/ConversionKey.hpp"
#include "parka/util/FlatMap.hpp"

namespace parka::evaluation
{
	typedef Value& (*IntrinsicConversion) (Value& to, const Value& from);

	FlatMap<validation::ConversionKey, IntrinsicConversion> getIntrinsicConversions();
}

#endif
