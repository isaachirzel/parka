#include "parka/enum/ContextType.hpp"

namespace parka
{
	std::ostream& operator<<(std::ostream& out, const ContextType& type)
	{
		switch (type)
		{
			case ContextType::Package:
				out << "package";
				break;

			case ContextType::Function:
				out << "function";
				break;

			case ContextType::Block:
				out << "block";
				break;

			default:
				out << '(' << (int)type << ") Invalid";
		}

		return out;
	}
}
