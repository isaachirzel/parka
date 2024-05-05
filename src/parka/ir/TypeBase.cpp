#include "parka/ir/TypeBase.hpp"

namespace parka::ir
{
	std::ostream& operator<<(std::ostream& out, const TypeBase& typeBase)
	{
		out << typeBase.symbol();

		return out;
	}
}
