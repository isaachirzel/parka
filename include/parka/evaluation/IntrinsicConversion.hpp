#ifndef PARKA_EVALUATION_INTRINSIC_CONVERSIONS_HPP
#define PARKA_EVALUATION_INTRINSIC_CONVERSIONS_HPP

#include "parka/evaluation/Value.hpp"
#include <functional>

namespace parka::evaluation
{
	typedef Value& (*IntrinsicConversion) (Value& to, const Value& from);

	extern IntrinsicConversion intrinsicConversions[];
	extern const usize intrinsicConversionCount;
}

#endif
