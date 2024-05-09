#ifndef PARKA_AST_FOR_EXPRESSION_HPP
#define PARKA_AST_FOR_EXPRESSION_HPP

#include "parka/ast/ExpressionAst.hpp"
#include "parka/ast/IdentifierAst.hpp"
#include "parka/ast/KeywordAst.hpp"
#include "parka/ast/RangeAst.hpp"
#include "parka/enum/ExpressionType.hpp"

namespace parka::ast
{
	class ForRangeStatementAst: public StatementAst
	{
		Snippet _snippet;
		KeywordAst _forKeyword;
		Identifier _variableName;
		RangeAst _range;

	public:

		ForRangeStatementAst(KeywordAst&& forKeyword, Identifier&& variableName, RangeAst&& range):
			ExpressionAst(ExpressionType::ForRange),
			_snippet(forKeyword.snippet() + range.snippet()),
			_forKeyword(std::move(forKeyword)),
			_variableName(std::move(variableName)),
			_range(std::move(range))
		{}

		const Snippet& snippet() const { return _snippet; }
		const auto& forKeyword() const { return _forKeyword; }
		const auto& variableName() const { return _variableName; }
		const auto& range() const { return _range; }
	};
}

#endif
