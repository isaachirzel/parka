#ifndef PARKA_AST_EXPRESSION_ASSIGNMENT_HPP
#define PARKA_AST_EXPRESSION_ASSIGNMENT_HPP

#include "parka/enum/AssignmentType.hpp"
#include "parka/ast/Expression.hpp"

namespace parka::ast
{
	class AssignmentExpressionAst : public ExpressionAst
	{
		Snippet _snippet;
		ExpressionAst& _lhs;
		ExpressionAst& _rhs;
		AssignmentType _assignmentType;

	public:

		AssignmentExpressionAst(ExpressionAst& lhs, ExpressionAst& rhs, AssignmentType assignmentType) :
		ExpressionAst(ExpressionType::Assignment),
		_snippet(lhs.snippet() + rhs.snippet()),
		_lhs(lhs),
		_rhs(rhs),
		_assignmentType(assignmentType)
		{}
		AssignmentExpressionAst(AssignmentExpressionAst&&) = default;
		AssignmentExpressionAst(const AssignmentExpressionAst&) = delete;

		static ExpressionAst *parse(Token& token);
		ir::ExpressionIr *validate(SymbolTable& symbolTable);

		const Snippet& snippet() const { return _snippet; }
		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
		const auto& assignmentType() const { return _assignmentType; }
	};
}

#endif
