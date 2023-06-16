#include "parka/ast/AssignmentExpression.hpp"
#include "parka/ir/AssignmentExpression.hpp"
#include "parka/log/Log.hpp"
#include "parka/ast/ConditionalExpression.hpp"

namespace parka::ast
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

	ExpressionAst *AssignmentExpressionAst::parse(Token& token)
	{
		auto *lhs = ConditionalExpressionAst::parse(token);

		if (!lhs)
			return {};

		auto type = getAssignmentType(token);

		if (!type)
			return lhs;

		token.increment();

		auto rhs = ConditionalExpressionAst::parse(token);

		if (!rhs)
			return {};

		auto *expression = new AssignmentExpressionAst(*lhs, *rhs, *type);

		return expression;
	}

	ir::ExpressionIr *AssignmentExpressionAst::validate(SymbolTable& symbolTable)
	{
		auto *lhs = _lhs.validate(symbolTable);
		auto *rhs = _rhs.validate(symbolTable);

		if (!lhs || !rhs)
			return {};

		// TODO: Operators and actualy get return type
		const auto& lhsType = lhs->valueType();
		const auto& rhsType = rhs->valueType();

		if (!rhsType.canConvertTo(lhsType))
		{
			log::error("Unable to add $ to $.", rhsType, lhsType);
			return nullptr;
		}
		
		auto *context = new ir::AssignmentExpressionIr(*lhs, *rhs, _assignmentType);

		return context;
	}
}
