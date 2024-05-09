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

			case StatementType::Return:
				out << "return";
				break;

			case StatementType::Break:
				out << "break";
				break;

			case StatementType::Continue:
				out << "continue";
				break;

			case StatementType::Yield:
				out << "yield";
				break;

			case StatementType::For:
				out << "for";
				break;

			default:
				out << '(' << (int)type << ") Invalid";
		}

		return out;
	}
}
