#ifndef PARKA_AST_EXPRESSION_BITWISE_XOR_HPP
#define PARKA_AST_EXPRESSION_BITWISE_XOR_HPP

#include "parka/ast/Expression.hpp"
#include "parka/enum/ExpressionType.hpp"

namespace parka::ast
{
	class BitwiseXorExpressionAst : public ExpressionAst
	{
		Snippet _snippet;
		ExpressionAst& _lhs;
		ExpressionAst& _rhs;

	public:

		BitwiseXorExpressionAst(ExpressionAst& lhs, ExpressionAst& rhs) :
		ExpressionAst(ExpressionType::BitwiseXor),
		_snippet(lhs.snippet() + rhs.snippet()),
		_lhs(lhs),
		_rhs(rhs)
		{}
		BitwiseXorExpressionAst(BitwiseXorExpressionAst&&) = default;
		BitwiseXorExpressionAst(const BitwiseXorExpressionAst&) = delete;

		static ExpressionAst *parse(Token& token);
		ir::ExpressionIr *validate(SymbolTable& symbolTable);

		const Snippet& snippet() const { return _snippet; }
		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
	};
}

#endif
