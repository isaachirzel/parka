#ifndef PARKA_AST_EXPRESSION_EQUALITY_HPP
#define PARKA_AST_EXPRESSION_EQUALITY_HPP

#include "parka/enum/EqualityType.hpp"
#include "parka/ast/Expression.hpp"

namespace parka::ast
{
	class EqualityExpressionAst : public ExpressionAst
	{
		Snippet _snippet;
		ExpressionAst& _lhs;
		ExpressionAst& _rhs;
		EqualityType _type;

	public:

		EqualityExpressionAst(ExpressionAst& lhs, ExpressionAst& rhs, EqualityType type) :
		_snippet(lhs.snippet() + rhs.snippet()),
		_lhs(lhs),
		_rhs(rhs),
		_type(type)
		{}
		EqualityExpressionAst(EqualityExpressionAst&&) = default;
		EqualityExpressionAst(const EqualityExpressionAst&) = delete;

		static ExpressionAst *parse(Token& token);
		ir::ExpressionIr *validate(SymbolTable& symbolTable);

		ExpressionType expressionType() const { return ExpressionType::Equality; }
		const Snippet& snippet() const { return _snippet; }
		
		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
		const auto& type() const { return _type; }
	};
}

#endif
