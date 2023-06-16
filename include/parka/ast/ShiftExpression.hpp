#ifndef PARKA_AST_EXPRESSION_SHIFT_HPP
#define PARKA_AST_EXPRESSION_SHIFT_HPP

#include "parka/enum/ShiftType.hpp"
#include "parka/ast/Expression.hpp"

namespace parka::ast
{
	class ShiftExpressionAst : public ExpressionAst
	{
		Snippet _snippet;
		ExpressionAst& _lhs;
		ExpressionAst& _rhs;
		ShiftType _type;

	public:

		ShiftExpressionAst(ExpressionAst& lhs, ExpressionAst& rhs, ShiftType type) :
		_snippet(lhs.snippet() + rhs.snippet()),
		_lhs(lhs),
		_rhs(rhs),
		_type(type)
		{}
		ShiftExpressionAst(ShiftExpressionAst&&) = default;
		ShiftExpressionAst(const ShiftExpressionAst&) = delete;

		static ExpressionAst *parse(Token& token);
		ir::ExpressionIr *validate(SymbolTable& symbolTable);

		ExpressionType expressionType() const { return ExpressionType::Shift; }
		const Snippet& snippet() const { return _snippet; }

		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
	};
}

#endif
