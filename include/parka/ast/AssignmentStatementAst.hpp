#ifndef PARKA_AST_ASSIGNMENT_STATEMENT_AST_HPP
#define PARKA_AST_ASSIGNMENT_STATEMENT_AST_HPP

#include "parka/ast/ExpressionAst.hpp"
#include "parka/ast/StatementAst.hpp"
#include "parka/enum/AssignmentType.hpp"
#include "parka/enum/StatementType.hpp"

namespace parka::ast
{
	class AssignmentStatementAst: public StatementAst
	{
		fs::FileSnippet _snippet;
		ExpressionAst& _identifier;
		ExpressionAst& _value;
		AssignmentType _assignmentType;

	public:

		AssignmentStatementAst(const fs::FileSnippet& snippet, ExpressionAst& identifier, ExpressionAst& value, AssignmentType assignmentType):
			StatementAst(StatementType::Assignment),
			_snippet(snippet),
			_identifier(identifier),
			_value(value),
			_assignmentType(assignmentType)
		{}
		AssignmentStatementAst(AssignmentStatementAst&&) = default;
		AssignmentStatementAst(const AssignmentStatementAst&) = delete;

		const fs::FileSnippet& snippet() const { return _snippet; }
		const auto& identifier() const { return _identifier; }
		const auto& value() const { return _value; }
		const auto& assignmentType() const { return _assignmentType; }
	};
}

#endif
