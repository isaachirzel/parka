#ifndef PARKA_AST_ADDITIVE_EXPRESSION_HPP
#define PARKA_AST_ADDITIVE_EXPRESSION_HPP

#include "parka/ast/Expression.hpp"
#include "parka/enum/AdditiveType.hpp"

namespace parka::ast
{
	class AdditiveExpressionAst : public ExpressionAst
	{
		Snippet _snippet;
		ExpressionAst& _lhs;
		ExpressionAst& _rhs;
		AdditiveType _additiveType;
		
	public:

		AdditiveExpressionAst(ExpressionAst& lhs, ExpressionAst& rhs, AdditiveType additiveType) :
		ExpressionAst(ExpressionType::Additive),
		_snippet(lhs.snippet() + rhs.snippet()),
		_lhs(lhs),
		_rhs(rhs),
		_additiveType(additiveType)
		{}
		AdditiveExpressionAst(AdditiveExpressionAst&&) = default;
		AdditiveExpressionAst(AdditiveExpressionAst&) = delete;

		static ExpressionAst *parse(Token& token);
		ir::ExpressionIr *validate(SymbolTable& symbolTable);

		const Snippet& snippet() const { return _snippet; }
		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
		const auto& additiveType() const { return _additiveType; }
	};
}

#endif
