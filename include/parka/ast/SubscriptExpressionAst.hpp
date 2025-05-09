#ifndef PARKA_AST_EXPRESSION_INDEX_HPP
#define PARKA_AST_EXPRESSION_INDEX_HPP

#include "parka/ast/ExpressionAst.hpp"
#include "parka/ir/ExpressionIr.hpp"

#include <utility>

namespace parka::ast
{
	class SubscriptExpressionAst: public ExpressionAst
	{
		fs::FileSnippet _snippet;
		ExpressionAst& _primary;
		ExpressionAst& _index;

	public:

		SubscriptExpressionAst(const fs::FileSnippet& snippet, ExpressionAst& primary, ExpressionAst& index):
		ExpressionAst(ExpressionType::Subscript),
		_snippet(snippet),
		_primary(primary),
		_index(index)
		{}
		SubscriptExpressionAst(SubscriptExpressionAst&&) = default;
		SubscriptExpressionAst(const SubscriptExpressionAst&) = delete;

		const fs::FileSnippet& snippet() const { return _snippet; }
		const auto& expression() const { return _primary; }
		const auto& index() const { return _index; }
	};
}

#endif
