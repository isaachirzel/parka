#ifndef PARKA_AST_FOR_EXPRESSION_HPP
#define PARKA_AST_FOR_EXPRESSION_HPP

#include "parka/ast/Expression.hpp"
#include "parka/ast/Identifier.hpp"
#include "parka/ast/Keyword.hpp"
#include "parka/ast/RangeAst.hpp"
#include "parka/enum/ExpressionType.hpp"
namespace parka::ast
{
	class ForRangeExpression: public ExpressionAst
	{
		Snippet _snippet;
		KeywordAst _forKeyword;
		Identifier _variableName;
		RangeAst _range;

	public:

		ForRangeExpression(KeywordAst&& forKeyword, Identifier&& variableName, RangeAst&& range):
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
