#include "parka/ast/expression/assignment.hpp"
#include "parka/ast/expression/additive.hpp"
#include "parka/ast/expression/conditional.hpp"
#include "parka/ast/module.hpp"
#include "parka/symbol/node_bank.hpp"
#include "parka/util/print.hpp"

Optional<AssignmentType> getAssignmentType(Token& token)
{
	switch (token.type())
	{
		case TokenType::Assign:
			return ASSIGNMENT_BECOME;

		case TokenType::MultiplyAssign:
			return ASSIGNMENT_MULTIPLY;

		case TokenType::DivideAssign:
			return ASSIGNMENT_DIVIDE;

		case TokenType::ModulusAssign:
			return ASSIGNMENT_MODULUS;

		case TokenType::AddAssign:
			return ASSIGNMENT_ADD;

		case TokenType::SubtractAssign:
			return ASSIGNMENT_SUBTRACT;

		case TokenType::LeftBitShiftAssign:
			return ASSIGNMENT_LEFT_BIT_SHIFT;

		case TokenType::RightBitShiftAssign:
			return ASSIGNMENT_RIGHT_BIT_SHIFT;

		case TokenType::BitwiseAndAssign:
			return ASSIGNMENT_BITWISE_AND;

		case TokenType::BitwiseOrAssign:
			return ASSIGNMENT_BITWISE_OR;

		case TokenType::BitwiseXorAssign:
			return ASSIGNMENT_BITWISE_XOR;
		
		default:
			return {};
	}
}

Optional<ExpressionId> Assignment::parse(Token& token)
{
	auto lhs = ConditionalExpression::parse(token);

	if (!lhs)
		return {};

	auto type = getAssignmentType(token);

	if (!type)
		return lhs;

	token.increment();

	auto rhs = ConditionalExpression::parse(token);

	if (!rhs)
		return {};

	auto expression = Assignment(lhs.unwrap(), rhs.unwrap(), type.unwrap());
	auto id = NodeBank::add(std::move(expression));

	return id;
}

bool Assignment::validate(LocalSymbolTable& symbols)
{
	bool success = true;

	if (!NodeBank::get(_lhs).validate(symbols))
		success = false;

	if (!NodeBank::get(_rhs).validate(symbols))
		success = false;

	// TODO: validate type of assignment

	return success;
}

Optional<Type> Assignment::getType(const LocalSymbolTable& symbolTable, Ref<Type> expected) const
{
	exitNotImplemented(here());
}
