#include "parka/validation/IntrinsicFunction.hpp"
#include "parka/ir/IntrinsicFunctionIr.hpp"
#include "parka/validation/IntrinsicFunctionEntry.hpp"

namespace parka::validation
{
	void addIntrinsicFunctions(Array<IntrinsicFunctionEntry>& functions, FlatMap<String, Resolvable*>& symbols)
	{
		auto& item = functions.push(IntrinsicFunctionEntry(ir::IntrinsicFunctionIr::printFunction));

		symbols.insert(ir::IntrinsicFunctionIr::printFunction.symbol(), &item);
	}
}
