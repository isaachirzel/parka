#ifndef PARKA_AST_YIELD_STATEMENT_AST_HPP
#define PARKA_AST_YIELD_STATEMENT_AST_HPP

#include "parka/ast/ExpressionAst.hpp"
#include "parka/ast/KeywordAst.hpp"
#include "parka/ast/StatementAst.hpp"

namespace parka::ast
{
	class YieldStatementAst: public StatementAst
	{
		Snippet _snippet;
		KeywordAst _keyword;
		ExpressionAst& _value;

	public:

		YieldStatementAst(KeywordAst&& keyword, ExpressionAst& value):
			StatementAst(StatementType::Return),
			_snippet(keyword.snippet() + value.snippet()),
			_keyword(std::move(keyword)),
			_value(value)
		{}
		YieldStatementAst(YieldStatementAst&&) = default;
		YieldStatementAst(const YieldStatementAst&) = delete;

		const Snippet& snippet() const { return _snippet; }
		const auto& keyword() const { return _keyword; }
		const auto& value() const { return _value; }
	};
}

#endif
