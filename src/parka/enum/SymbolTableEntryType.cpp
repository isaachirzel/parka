#include "parka/enum/SymbolTableEntryType.hpp"

namespace parka
{
	std::ostream& operator<<(std::ostream& out, const SymbolTableEntryType& type)
	{
		switch (type)
		{
			case SymbolTableEntryType::Package:
				out << "package";
				break;

			case SymbolTableEntryType::Struct:
				out << "struct";
				break;

			case SymbolTableEntryType::Primitive:
				out << "primitive";
				break;

			case SymbolTableEntryType::Function:
				out << "function";
				break;

			case SymbolTableEntryType::Variable:
				out << "variable";
				break;

			case SymbolTableEntryType::Parameter:
				out << "parameter";
				break;

			case SymbolTableEntryType::Member:
				out << "member";
				break;
		}

		return out;
	}
}
