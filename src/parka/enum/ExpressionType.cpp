#include "parka/enum/ExpressionType.hpp"

namespace parka
{
	std::ostream& operator<<(std::ostream& out, const ExpressionType& type)
	{
		switch (type)
		{
			case ExpressionType::Binary:
				out << "BinaryExpression";
				break;

			case ExpressionType::Block:
				out << "Block";
				break;

			case ExpressionType::Call:
				out << "CallExpression";
				break;

			case ExpressionType::Conditional:
				out << "ConditionalExpression";
				break;

			case ExpressionType::Identifier:
				out << "IdentifierExpression";
				break;

			case ExpressionType::If:
				out << "IfExpression";
				break;

			case ExpressionType::Subscript:
				out << "SubscriptExpression";
				break;

			case ExpressionType::MemberAccess:
				out << "MemberAccessExpression";
				break;

			case ExpressionType::Prefix:
				out << "PrefixExpression";
				break;

			case ExpressionType::BoolLiteral:
				out << "BoolLiteral";
				break;

			case ExpressionType::CharLiteral:
				out << "CharLiteral";
				break;

			case ExpressionType::FloatLiteral:
				out << "FloatLiteral";
				break;

			case ExpressionType::IntegerLiteral:
				out << "IntegerLiteral";
				break;

			case ExpressionType::StringLiteral:
				out << "StringLiteral";
				break;

			default:
				out << "(" << (int)type << ") Invalid";
		}

		return out;
	}
}