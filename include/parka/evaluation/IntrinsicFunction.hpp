#ifndef PARKA_EVALUATION_INTRINSIC_FUNCTION_HPP
#define PARKA_EVALUATION_INTRINSIC_FUNCTION_HPP

#include "parka/evaluation/Value.hpp"
#include "parka/util/Array.hpp"

namespace parka::evaluation
{
	typedef Value& (*IntrinsicFunction)(const Array<Value*>& values);
	
	
}

#endif
1