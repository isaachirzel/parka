#include <warbler/syntax/statement/assignment_statement.hpp>

// local headers
#include <warbler/util/print.hpp>

// standard headers
#include <cstdlib>

namespace warbler::syntax
{
	AssignmentStatement::AssignmentStatement(Expression&& lhs, Expression&& rhs, AssignmentType type) :
	_lhs(std::move(lhs)),
	_rhs(std::move(rhs)),
	_type(type)
	{}

	Result<AssignmentStatement> AssignmentStatement::parse(lexicon::Token& token)
	{
		auto lhs = PrefixExpression::parse(token.next());

		if (!lhs)
			return {};

		AssignmentType type;
		switch (token.type())
		{
			case lexicon::TokenType::Assign:
				type = AssignmentType::Become;
				break;

			case lexicon::TokenType::MultiplyAssign:
				type = AssignmentType::Multiply;
				break;

			case lexicon::TokenType::DivideAssign:
				type = AssignmentType::Divide;
				break;

			case lexicon::TokenType::ModulusAssign:
				type = AssignmentType::Modulus;
				break;

			case lexicon::TokenType::AddAssign:
				type = AssignmentType::Add;
				break;

			case lexicon::TokenType::SubtractAssign:
				type = AssignmentType::Subtract;
				break;

			case lexicon::TokenType::LeftBitShiftAssign:
				type = AssignmentType::LeftBitShift;
				break;

			case lexicon::TokenType::RightBitShiftAssign:
				type = AssignmentType::RightBitShift;
				break;

			case lexicon::TokenType::BitwiseAndAssign:
				type = AssignmentType::BitwiseAnd;
				break;

			case lexicon::TokenType::BitwiseOrAssign:
				type = AssignmentType::BitwiseOr;
				break;

			case lexicon::TokenType::BitwiseXorAssign:
				type = AssignmentType::BitwiseXor;
				break;

			default:
				print_parse_error(token, "expected assignment operator after primary expression");
				return {};
		}

		auto rhs = Expression::parse(token.next());

		if (!rhs)
			return {};

		if (token.type() != lexicon::TokenType::Semicolon)
		{
			print_parse_error(token, "';' after assignment");
			return {};
		}

		token.next();

		return AssignmentStatement(lhs.unwrap(), rhs.unwrap(), type);
	}

	// bool AssignmentStatement::validate(semantics::Context& context)
	// {
	// 	throw std::runtime_error("AssignmentStatement::validate is not implemented yet");
	// }

	// void AssignmentStatement::print_tree(u32 depth) const
	// {
	// 	_lhs->print_tree(depth);

	// 	switch (_type)
	// 	{
	// 		case AssignmentType::Become:
	// 			print_branch(depth, "=");
	// 			break;

	// 		case AssignmentType::Multiply:
	// 			print_branch(depth, "*=");
	// 			break;

	// 		case AssignmentType::Divide:
	// 			print_branch(depth, "/=");
	// 			break;

	// 		case AssignmentType::Modulus:
	// 			print_branch(depth, "%=");		
	// 			break;

	// 		case AssignmentType::Add:
	// 			print_branch(depth, "*=");
	// 			break;

	// 		case AssignmentType::Subtract:
	// 			print_branch(depth, "-=");				
	// 			break;

	// 		case AssignmentType::LeftBitShift:
	// 			print_branch(depth, "<<=");
	// 			break;

	// 		case AssignmentType::RightBitShift:
	// 			print_branch(depth, ">>=");
	// 			break;

	// 		case AssignmentType::BitwiseAnd:
	// 			print_branch(depth, "&=");
	// 			break;

	// 		case AssignmentType::BitwiseOr:
	// 			print_branch(depth, "|=");
	// 			break;

	// 		case AssignmentType::BitwiseXor:
	// 			print_branch(depth, "^=");
	// 			break;
	// 	}

	// 	_rhs->print_tree(depth + 1);
	// }
}
