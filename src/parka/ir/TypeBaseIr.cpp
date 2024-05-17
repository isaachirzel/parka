#include "parka/ir/TypeBaseIr.hpp"

namespace parka::ir
{
	std::ostream& operator<<(std::ostream& out, const TypeBaseIr& typeBase)
	{
		out << typeBase.symbol();

		return out;
	}
}
