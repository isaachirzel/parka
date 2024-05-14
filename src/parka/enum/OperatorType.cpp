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

			case BinaryExpressionType::Subtract:
				return OperatorType::Subtract;

			case BinaryExpressionType::Multiply:
				return OperatorType::Multiply;

			case BinaryExpressionType::Divide:
				return OperatorType::Divide;

			case BinaryExpressionType::LessThan:
				return OperatorType::LessThan;

			case BinaryExpressionType::GreaterThan:
				return OperatorType::GreaterThan;

			case BinaryExpressionType::LessThanOrEqualTo:
				return OperatorType::LessThanOrEqualTo;

			case BinaryExpressionType::GreaterThanOrEqualTo:
				return OperatorType::GreaterThanOrEqualTo;

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
				out << "+";
				break;

			case OperatorType::Subtract:
				out << "-";
				break;

			case OperatorType::Multiply:
				out << "*";
				break;

			case OperatorType::Divide:
				out << "/";
				break;

			case OperatorType::LessThan:
				out << "<";
				break;

			case OperatorType::GreaterThan:
				out << ">";
				break;

			case OperatorType::LessThanOrEqualTo:
				out << "<=";
				break;

			case OperatorType::GreaterThanOrEqualTo:
				out << ">=";
				break;
				
			default:
				out << "(" << (int)type << ") Invalid";
		}

		return out;
	}
}
