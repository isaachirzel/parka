#ifndef PARKA_AST_YIELD_STATEMENT_AST_HPP
#define PARKA_AST_YIELD_STATEMENT_AST_HPP

#include "parka/ast/ExpressionAst.hpp"
#include "parka/ast/StatementAst.hpp"

namespace parka::ast
{
	class YieldStatementAst: public StatementAst
	{
		fs::FileSnippet _snippet;
		ExpressionAst& _value;

	public:

		YieldStatementAst(const fs::FileSnippet& snippet, ExpressionAst& value):
			StatementAst(StatementType::Return),
			_snippet(snippet),
			_value(value)
		{}
		YieldStatementAst(YieldStatementAst&&) = default;
		YieldStatementAst(const YieldStatementAst&) = delete;

		const fs::FileSnippet& snippet() const { return _snippet; }
		const auto& value() const { return _value; }
	};
}

#endif
