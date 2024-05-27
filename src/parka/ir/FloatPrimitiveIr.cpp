#include "parka/ir/FloatPrimitiveIr.hpp"

namespace parka::ir
{
	FloatPrimitiveIr FloatPrimitiveIr::instance;

	FloatPrimitiveIr::FloatPrimitiveIr():
		TypeIr(TypeCategory::Float)
	{}

	std::ostream& FloatPrimitiveIr::printType(std::ostream& out) const
	{
		out << "float";

		return out;
	}
}
