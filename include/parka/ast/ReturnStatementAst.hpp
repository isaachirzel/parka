#ifndef PARKA_AST_RETURN_STATEMENT_AST_HPP
#define PARKA_AST_RETURN_STATEMENT_AST_HPP

#include "parka/ast/ExpressionAst.hpp"
#include "parka/ast/KeywordAst.hpp"
#include "parka/ast/StatementAst.hpp"

namespace parka::ast
{
	class ReturnStatementAst: public StatementAst
	{
		Snippet _snippet;
		KeywordAst _keyword;
		ExpressionAst *_value;

	public:

		ReturnStatementAst(KeywordAst&& keyword, ExpressionAst& value):
			StatementAst(StatementType::Return),
			_snippet(keyword.snippet() + value.snippet()),
			_keyword(std::move(keyword)),
			_value(&value)
		{}
		ReturnStatementAst(KeywordAst&& keyword):
			StatementAst(StatementType::Return),
			_snippet(keyword.snippet()),
			_keyword(std::move(keyword)),
			_value(nullptr)
		{}
		ReturnStatementAst(ReturnStatementAst&&) = default;
		ReturnStatementAst(const ReturnStatementAst&) = delete;

		const Snippet& snippet() const { return _snippet; }
		const auto& keyword() const { return _keyword; }
		bool hasValue() const { return !!_value; }
		const auto& value() const { return *_value; }
	};
}

#endif
