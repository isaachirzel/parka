#ifndef WARBLER_SYNTAX_EXPRESSION_ASSIGNMENT_HPP
#define WARBLER_SYNTAX_EXPRESSION_ASSIGNMENT_HPP

// local headers
#include <warbler/syntax//statement/statement.hpp>
#include <warbler/syntax//expression/expression.hpp>
#include <warbler/syntax//expression/conditional_expression.hpp>

namespace warbler::syntax
{
	enum AssignmentType
	{
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

	class AssignmentStatement : public Statement
	{
	private:

		Ptr<Expression> _lhs;
		Ptr<Expression> _rhs;
		AssignmentType _type;

	public:

		AssignmentStatement(Ptr<Expression>&& lhs, Ptr<Expression> &&rhs, AssignmentType type);

		static Result<AssignmentStatement> parse(TokenIterator& iter);

		bool validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx);
		void print_tree(u32 depth = 0) const;
	};
}
#endif
