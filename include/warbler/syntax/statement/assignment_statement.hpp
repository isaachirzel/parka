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

		Ptr<Expression> _lhs;
		Ptr<Expression> _rhs;
		AssignmentType _type;

	public:

		AssignmentStatement(Ptr<Expression>&& lhs, Ptr<Expression> &&rhs, AssignmentType type);

		static Result<AssignmentStatement> parse(lexicon::TokenIterator& iter);

		bool validate(semantics::ModuleContext& mod_ctx, semantics::FunctionContext& func_ctx);
		void print_tree(u32 depth = 0) const;
	};
}
#endif
