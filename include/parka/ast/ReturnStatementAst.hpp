#ifndef PARKA_AST_RETURN_STATEMENT_AST_HPP
#define PARKA_AST_RETURN_STATEMENT_AST_HPP

#include "parka/ast/ExpressionAst.hpp"
#include "parka/ast/StatementAst.hpp"

namespace parka::ast
{
	class ReturnStatementAst: public StatementAst
	{
		fs::FileSnippet _snippet;
		ExpressionAst *_value;

	public:

		ReturnStatementAst(const fs::FileSnippet& snippet, ExpressionAst* value):
			StatementAst(StatementType::Return),
			_snippet(snippet),
			_value(value)
		{}
		ReturnStatementAst(ReturnStatementAst&&) = default;
		ReturnStatementAst(const ReturnStatementAst&) = delete;

		const fs::FileSnippet& snippet() const { return _snippet; }
		bool hasValue() const { return !!_value; }
		const auto& value() const { return *_value; }
	};
}

#endif
