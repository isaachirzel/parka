#include "parka/enum/BinaryExpressionType.hpp"

namespace parka
{
	std::ostream& operator<<(std::ostream& out, const BinaryExpressionType& binaryExpressionType)
	{
		switch (binaryExpressionType)
		{
			case BinaryExpressionType::Add:
				out << "+";
				break;

			case BinaryExpressionType::Subtract:
				out << "-";
				break;

			case BinaryExpressionType::Multiply:
				out << "*";
				break;

			case BinaryExpressionType::Divide:
				out << "/";
				break;

			case BinaryExpressionType::Modulus:
				out << "%";
				break;

			case BinaryExpressionType::BooleanOr:
				out << "||";
				break;
				
			case BinaryExpressionType::BooleanAnd:
				out << "&&";
				break;
				
			case BinaryExpressionType::BitwiseOr:
				out << "|";
				break;
				
			case BinaryExpressionType::BitwiseXor:
				out << "^";
				break;
				
			case BinaryExpressionType::BitwiseAnd:
				out << "&";
				break;

			case BinaryExpressionType::Equals:
				out << "==";
				break;

			case BinaryExpressionType::NotEquals:
				out << "!=";
				break;

			case BinaryExpressionType::LessThan:
				out << "<";
				break;

			case BinaryExpressionType::GreaterThan:
				out << ">";
				break;

			case BinaryExpressionType::LessThanOrEqualTo:
				out << "<=";
				break;

			case BinaryExpressionType::GreaterThanOrEqualTo:
				out << ">=";
				break;

			case BinaryExpressionType::LeftShift:
				out << "<<";
				break;

			case BinaryExpressionType::RightShift:
				out << ">>";
				break;
				
			default:
				out << "(BinaryExpressionType " << (int)binaryExpressionType << ")";
				break;
		}

		return out;
	}
}
