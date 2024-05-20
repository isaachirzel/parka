#ifndef PARKA_AST_FUNCTION_BODY_AST_HPP
#define PARKA_AST_FUNCTION_BODY_AST_HPP

#include "parka/ast/BlockStatementAst.hpp"
#include "parka/ast/ExpressionAst.hpp"
#include "parka/file/Snippet.hpp"

namespace parka::ast
{
	class FunctionBodyAst
	{
		Snippet _snippet;
		union
		{
			ExpressionAst* _expression;
			BlockStatementAst* _blockStatement;
		};
		bool _isExpression;

	public:

		FunctionBodyAst(const Snippet& snippet, ExpressionAst& expression);
		FunctionBodyAst(const Snippet& snippet, BlockStatementAst& blockStatement);
		FunctionBodyAst(FunctionBodyAst&& other);
		FunctionBodyAst(const FunctionBodyAst&) = delete;
		~FunctionBodyAst() = default;

		const Snippet& snippet() const { return _snippet; }
		const auto& isExpression() const { return _isExpression; }
		const auto& expression() const { assert(_isExpression); return *_expression; }
		const auto& blockStatement() const { assert(_blockStatement); return *_blockStatement; }
	};
}

#endif
