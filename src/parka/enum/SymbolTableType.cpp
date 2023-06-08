#include "parka/enum/SymbolTableType.hpp"

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
				out << '(' << (int)type << ") Invalid";
		}

		return out;
	}
}
