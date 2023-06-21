#include "parka/enum/StatementType.hpp"

namespace parka
{
	std::ostream& operator<<(std::ostream& out, const StatementType& type)
	{
		switch (type)
		{
			case StatementType::Declaration:
				out << "declaration";
				break;

			case StatementType::Expression:
				out << "expression";
				break;

			case StatementType::Jump:
				out << "jump";
				break;

			default:
				out << '(' << (int)type << ") Invalid";
		}

		return out;
	}
}
