#ifndef PARKA_AST_EXPRESSION_MULTIPLICATIVE_HPP
#define PARKA_AST_EXPRESSION_MULTIPLICATIVE_HPP

#include "parka/enum/MultiplicativeType.hpp"
#include "parka/ast/Expression.hpp"
#include "parka/util/Optional.hpp"

namespace parka::ast
{
	class MultiplicativeExpressionAst : public ExpressionAst
	{
		Snippet _snippet;
		ExpressionAst& _lhs;
		ExpressionAst& _rhs;
		MultiplicativeType _type;

	public:

		MultiplicativeExpressionAst(ExpressionAst& lhs, ExpressionAst& rhs, MultiplicativeType type) :
		ExpressionAst(ExpressionType::Multiplicative),
		_snippet(lhs.snippet() + rhs.snippet()),
		_lhs(lhs),
		_rhs(rhs),
		_type(type)
		{}
		MultiplicativeExpressionAst(MultiplicativeExpressionAst&&) = default;
		MultiplicativeExpressionAst(const MultiplicativeExpressionAst&) = delete;

		static ExpressionAst *parse(Token& token);
		ir::ExpressionIr *validate(SymbolTable&);

		const Snippet& snippet() const { return _snippet; }
		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
		const auto& type() const { return _type; }
	};
}

#endif
