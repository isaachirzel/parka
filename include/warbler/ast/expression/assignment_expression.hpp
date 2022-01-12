#ifndef WARBLER_AST_EXPRESSION_ASSIGNMENT_HPP
#define WARBLER_AST_EXPRESSION_ASSIGNMENT_HPP

// local headers
#include <warbler/ast/expression/primary_expression.hpp>
#include <warbler/ast/expression/conditional_expression.hpp>
#include <warbler/ast/expression/prefix.hpp>
namespace warbler
{
	enum AssignmentType
	{
		ASSIGN_NONE,
		ASSIGN_BECOME,
		ASSIGN_MULTIPLY,
		ASSIGN_DIVIDE,
		ASSIGN_MODULUS,
		ASSIGN_ADD,
		ASSIGN_SUBTRACT,
		ASSIGN_LSHIFT,
		ASSIGN_RSHIFT,
		ASSIGN_BITWISE_AND,
		ASSIGN_BITWISE_OR,
		ASSIGN_BITWISE_XOR
	};

	struct AssignmentExpression
	{
	private:

		PrimaryExpression _lhs;
		ConditionalExpression *_rhs;
		AssignmentType _type;

	public:

		AssignmentExpression(PrimaryExpression&& lhs, ConditionalExpression *rhs, AssignmentType type);

		static Result<AssignmentExpression> parse(TokenIterator& iter);

		void print_tree(u32 depth = 0) const;
	};
}
#endif
