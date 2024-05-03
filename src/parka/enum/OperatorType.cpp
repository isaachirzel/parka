#include "parka/enum/OperatorType.hpp"
#include "parka/enum/BinaryExpressionType.hpp"
#include "parka/log/Log.hpp"

namespace parka
{
	OperatorType toOperatorType(BinaryExpressionType type)
	{
		switch (type)
		{
			case BinaryExpressionType::Add:
				return OperatorType::Add;

			default:
				break;
		}

		log::fatal("Unable to get OperatorType for BinaryExpressionType: $", (int)type);
	}

	std::ostream& operator<<(std::ostream& out, const OperatorType& type)
	{
		switch (type)
		{
			case OperatorType::Add:
				out << "`+`";
				break;
				
			default:
				out << "(" << (int)type << ") Invalid";
		}

		return out;
	}
}
