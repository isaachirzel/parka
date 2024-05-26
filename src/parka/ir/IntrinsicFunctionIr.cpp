#include "parka/ir/IntrinsicFunctionIr.hpp"

namespace parka::ir
{
	IntrinsicFunctionIr IntrinsicFunctionIr::printFunction("print", PrototypeIr({}, TypeIr::voidType));
}
