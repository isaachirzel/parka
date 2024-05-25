#ifndef PARKA_AST_RETURN_STATEMENT_AST_HPP
#define PARKA_AST_RETURN_STATEMENT_AST_HPP

#include "parka/ast/ExpressionAst.hpp"
#include "parka/ast/StatementAst.hpp"

namespace parka::ast
{
	class ReturnStatementAst: public StatementAst
	{
		Snippet _snippet;
		ExpressionAst *_value;

	public:

		ReturnStatementAst(const Snippet& snippet, ExpressionAst* value):
			StatementAst(StatementType::Return),
			_snippet(snippet),
			_value(value)
		{}
		ReturnStatementAst(ReturnStatementAst&&) = default;
		ReturnStatementAst(const ReturnStatementAst&) = delete;

		const Snippet& snippet() const { return _snippet; }
		bool hasValue() const { return !!_value; }
		const auto& value() const { return *_value; }
	};
}

#endif
