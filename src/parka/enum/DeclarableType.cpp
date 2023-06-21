#include "parka/enum/DeclarableType.hpp"

namespace parka
{
	std::ostream& operator<<(std::ostream& out, const DeclarableType& declarableType)
	{
		switch (declarableType)
		{
			case DeclarableType::Struct:
				out << "struct";
				break;

			case DeclarableType::Function:
				out << "function";
				break;

			case DeclarableType::Variable:
				out << "variable";
				break;

			case DeclarableType::Parameter:
				out << "parameter";
				break;

			case DeclarableType::Member:
				out << "member";
				break;
		}

		return out;
	}
}
