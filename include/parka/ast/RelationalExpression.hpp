#ifndef PARKA_AST_EXPRESSION_RELATIONAL_HPP
#define PARKA_AST_EXPRESSION_RELATIONAL_HPP

#include "parka/enum/RelationalType.hpp"
#include "parka/ast/Expression.hpp"
#include "parka/ir/Expression.hpp"

namespace parka::ast
{
	class RelationalExpressionAst : public ExpressionAst
	{
		Snippet _snippet;
		ExpressionAst& _lhs;
		ExpressionAst& _rhs;
		RelationalType _type;

	public:

		RelationalExpressionAst(ExpressionAst& lhs, ExpressionAst& rhs, RelationalType type) :
		_snippet(lhs.snippet() + rhs.snippet()),
		_lhs(lhs),
		_rhs(rhs),
		_type(type)
		{}
		RelationalExpressionAst(RelationalExpressionAst&&) = default;
		RelationalExpressionAst(const RelationalExpressionAst&) = delete;

		static ExpressionAst *parse(Token& token);
		ir::ExpressionIr *validate(SymbolTable& symbolTable);

		ExpressionType expressionType() const { return ExpressionType::Relational; }
		const Snippet& snippet() const { return _snippet; }
		
		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
		const auto& type() const { return _type; }
	};
}

#endif
