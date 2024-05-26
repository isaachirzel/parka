#include "parka/enum/ResolvableType.hpp"

namespace parka
{
	std::ostream& operator<<(std::ostream& out, const ResolvableType& type)
	{
		switch (type)
		{
			case ResolvableType::Package:
				out << "package";
				break;

			case ResolvableType::Primitive:
				out << "primitive";
				break;

			case ResolvableType::Struct:
				out << "struct";
				break;

			case ResolvableType::Function:
				out << "function";
				break;

			case ResolvableType::Variable:
				out << "variable";
				break;

			case ResolvableType::Parameter:
				out << "parameter";
				break;

			case ResolvableType::Member:
				out << "member";
				break;
		}

		return out;
	}
}
