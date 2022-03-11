#ifndef WARBLER_SYNTAX_EXPRESSION_ASSIGNMENT_HPP
#define WARBLER_SYNTAX_EXPRESSION_ASSIGNMENT_HPP

// local headers
#include <warbler/syntax/statement/statement.hpp>
#include <warbler/syntax/expression/expression.hpp>
#include <warbler/syntax/expression/conditional_expression.hpp>

namespace warbler::syntax
{
	enum class AssignmentType
	{
		Become,
		Multiply,
		Divide,
		Modulus,
		Add,
		Subtract,
		LeftBitShift,
		RightBitShift,
		BitwiseAnd,
		BitwiseOr,
		BitwiseXor
	};

	class AssignmentStatement : public Statement
	{
	private:

		Expression _lhs;
		Expression _rhs;
		AssignmentType _type;

	public:

		AssignmentStatement(Expression&& lhs, Expression &&rhs, AssignmentType type);

		static Result<AssignmentStatement> parse(lexicon::Token& token);

		
		void print_tree(u32 depth = 0) const;
	};
}
#endif
