#include "parka/syntax/AssignmentExpressionSyntax.hpp"
#include "parka/syntax/ConditionalExpressionSyntax.hpp"

namespace parka
{
	static Optional<AssignmentType> getAssignmentType(Token& token)
	{
		switch (token.type())
		{
			case TokenType::Assign:
				return AssignmentType::Become;

			case TokenType::MultiplyAssign:
				return AssignmentType::Multiply;

			case TokenType::DivideAssign:
				return AssignmentType::Divide;

			case TokenType::ModulusAssign:
				return AssignmentType::Modulus;

			case TokenType::AddAssign:
				return AssignmentType::Add;

			case TokenType::SubtractAssign:
				return AssignmentType::Subtract;

			case TokenType::LeftBitShiftAssign:
				return AssignmentType::LeftShift;

			case TokenType::RightBitShiftAssign:
				return AssignmentType::RightShift;

			case TokenType::BitwiseAndAssign:
				return AssignmentType::BitwiseAnd;

			case TokenType::BitwiseOrAssign:
				return AssignmentType::BitwiseOr;

			case TokenType::BitwiseXorAssign:
				return AssignmentType::BitwiseXor;
			
			default:
				return {};
		}
	}

	ExpressionSyntax *AssignmentExpressionSyntax::parse(Token& token)
	{
		auto *lhs = ConditionalExpressionSyntax::parse(token);

		if (!lhs)
			return {};

		auto type = getAssignmentType(token);

		if (!type)
			return lhs;

		token.increment();

		auto rhs = ConditionalExpressionSyntax::parse(token);

		if (!rhs)
			return {};

		auto *expression = new AssignmentExpressionSyntax(*lhs, *rhs, *type);

		return expression;
	}
}
