#ifndef PARKA_AST_EXPRESSION_INDEX_HPP
#define PARKA_AST_EXPRESSION_INDEX_HPP

#include "parka/ast/Expression.hpp"
#include "parka/ir/Expression.hpp"

#include <utility>

namespace parka::ast
{
	class SubscriptExpressionAst : public ExpressionAst
	{
		Snippet _snippet;
		ExpressionAst& _primary;
		ExpressionAst& _index;

	public:

		SubscriptExpressionAst(const Snippet& snippet, ExpressionAst& primary, ExpressionAst& index) :
		_snippet(snippet),
		_primary(primary),
		_index(index)
		{}
		SubscriptExpressionAst(SubscriptExpressionAst&&) = default;
		SubscriptExpressionAst(const SubscriptExpressionAst&) = delete;

		static ExpressionAst *parse(Token& token, ExpressionAst& primary);
		ir::ExpressionIr *validate(SymbolTable& symbolTable);

		ExpressionType expressionType() const { return ExpressionType::Subscript; }
		const Snippet& snippet() const { return _snippet; }
		const auto& expression() const { return _primary; }
		const auto& index() const { return _index; }
	};
}

#endif
