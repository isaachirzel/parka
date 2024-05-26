#include "parka/ir/FunctionIr.hpp"
#include "parka/ir/VoidPrimitiveIr.hpp"

namespace parka::ir
{
	FunctionIr FunctionIr::printFunction("print", PrototypeIr({}, VoidPrimitiveIr::voidPrimitive));

	std::ostream& FunctionIr::printType(std::ostream& out) const
	{
		

		return out;
	}
}
