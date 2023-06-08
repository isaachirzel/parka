#include "parka/enum/ExpressionType.hpp"

namespace parka
{
	std::ostream& operator<<(std::ostream& out, const ExpressionType& type)
	{
		switch (type)
		{
			case ExpressionType::Additive:
				out << "AdditiveExpression";
				break;

			case ExpressionType::Assignment:
				out << "AssignmentExpression";
				break;

			case ExpressionType::BitwiseAnd:
				out << "BitwiseAndExpression";
				break;

			case ExpressionType::BitwiseOr:
				out << "BitwiseOrExpression";
				break;

			case ExpressionType::BitwiseXor:
				out << "BitwiseXorExpression";
				break;

			case ExpressionType::Block:
				out << "BlockExpression";
				break;

			case ExpressionType::BooleanAnd:
				out << "BooleanAndExpression";
				break;

			case ExpressionType::BooleanOr:
				out << "BooleanOrExpression";
				break;

			case ExpressionType::Call:
				out << "CallExpression";
				break;

			case ExpressionType::Conditional:
				out << "ConditionalExpression";
				break;

			case ExpressionType::Equality:
				out << "EqualityExpression";
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

			case ExpressionType::Multiplicative:
				out << "MultiplicativeExpression";
				break;

			case ExpressionType::Prefix:
				out << "PrefixExpression";
				break;

			case ExpressionType::Relational:
				out << "RelationalExpression";
				break;

			case ExpressionType::Shift:
				out << "ShiftExpression";
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