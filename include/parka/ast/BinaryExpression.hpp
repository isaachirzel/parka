#ifndef PARKA_AST_BINARY_EXPRESSION_HPP
#define PARKA_AST_BINARY_EXPRESSION_HPP

#include "parka/ast/Expression.hpp"
#include "parka/enum/BinaryExpressionType.hpp"
#include "parka/file/Snippet.hpp"

namespace parka::ast
{
	class BinaryExpressionAst: public ExpressionAst
	{
		Snippet _snippet;
		ExpressionAst& _lhs;
		ExpressionAst& _rhs;
		BinaryExpressionType _binaryExpressionType;

	public:

		BinaryExpressionAst(ExpressionAst& lhs, ExpressionAst& rhs, BinaryExpressionType binaryExpressionType):
		ExpressionAst(ExpressionType::Binary),
		_snippet(lhs.snippet() + rhs.snippet()),
		_lhs(lhs),
		_rhs(rhs),
		_binaryExpressionType(binaryExpressionType)
		{}

		const Snippet& snippet() const { return _snippet; }
		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
		const auto& binaryExpressionType() const { return _binaryExpressionType; }
	};
}

#endif
