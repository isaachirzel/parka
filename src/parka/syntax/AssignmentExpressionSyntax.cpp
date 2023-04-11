#include "parka/syntax/AssignmentExpressionSyntax.hpp"
#include "parka/syntax/AdditiveExpressionSyntax.hpp"
#include "parka/syntax/ConditionalExpressionSyntax.hpp"
#include "parka/syntax/ModuleSyntax.hpp"
#include "parka/Storage.hpp"
#include "parka/util/Print.hpp"

namespace parka
{
	Optional<AssignmentType> getAssignmentType(Token& token)
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

	Optional<ExpressionId> AssignmentExpressionSyntax::parse(Token& token)
	{
		auto lhs = ConditionalExpressionSyntax::parse(token);

		if (!lhs)
			return {};

		auto type = getAssignmentType(token);

		if (!type)
			return lhs;

		token.increment();

		auto rhs = ConditionalExpressionSyntax::parse(token);

		if (!rhs)
			return {};

		auto expression = AssignmentExpressionSyntax(*lhs, *rhs, *type);
		auto id = Storage::add(std::move(expression));

		return id;
	}

	// bool Assignment::validate(const EntityId& functionId)
	// {
	// 	bool success = true;

	// 	if (!Storage::get(_lhs).validate(functionId))
	// 		success = false;

	// 	if (!Storage::get(_rhs).validate(functionId))
	// 		success = false;

	// 	// TODO: validate type of assignment

	// 	return success;
	// }
}
