#ifndef PARKA_AST_FOR_EXPRESSION_HPP
#define PARKA_AST_FOR_EXPRESSION_HPP

#include "parka/ast/IdentifierAst.hpp"
#include "parka/ast/KeywordAst.hpp"
#include "parka/ast/RangeAst.hpp"
#include "parka/ast/StatementAst.hpp"

namespace parka::ast
{
	class ForStatementAst: public StatementAst
	{
		Snippet _snippet;
		KeywordAst _forKeyword;
		Identifier _variableName;
		RangeAst _range;
		ExpressionAst& _body;

	public:

		ForStatementAst(KeywordAst&& forKeyword, Identifier&& variableName, RangeAst&& range, ExpressionAst& body):
			StatementAst(StatementType::For),
			_snippet(forKeyword.snippet() + range.snippet()),
			_forKeyword(std::move(forKeyword)),
			_variableName(std::move(variableName)),
			_range(std::move(range)),
			_body(body)
		{}

		const Snippet& snippet() const { return _snippet; }
		const auto& forKeyword() const { return _forKeyword; }
		const auto& variableName() const { return _variableName; }
		const auto& range() const { return _range; }
		const auto& body() const { return _body; }
	};
}

#endif
