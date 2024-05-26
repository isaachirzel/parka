#ifndef PARKA_VALIDATION_INTRINSIC_FUNCTION_HPP
#define PARKA_VALIDATION_INTRINSIC_FUNCTION_HPP

#include "parka/validation/IntrinsicFunctionEntry.hpp"
#include "parka/validation/Resolvable.hpp"

namespace parka::validation
{
	void addIntrinsicFunctions(Array<IntrinsicFunctionEntry>& functions, FlatMap<String, Resolvable*>& symbols);
}

#endif
