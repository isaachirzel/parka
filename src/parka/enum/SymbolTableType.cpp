#include "parka/enum/SymbolTableType.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	std::ostream& operator<<(std::ostream& out, const SymbolTableType& type)
	{
		switch (type)
		{
			case SymbolTableType::Package:
				out << "package";
				break;

			case SymbolTableType::Function:
				out << "function";
				break;

			case SymbolTableType::Block:
				out << "block";
				break;

			default:
				out << '(' << (int)type << ") invalid";
		}

		return out;
	}
}
