#ifndef PARKA_AST_FUNCTION_BODY_AST_HPP
#define PARKA_AST_FUNCTION_BODY_AST_HPP

#include "parka/ast/BlockStatementAst.hpp"
#include "parka/ast/ExpressionAst.hpp"
#include "parka/fs/FileSnippet.hpp"

namespace parka::ast
{
	class FunctionBodyAst
	{
		fs::FileSnippet _snippet;
		union
		{
			ExpressionAst* _expression;
			BlockStatementAst* _blockStatement;
		};
		bool _isExpression;

	public:

		FunctionBodyAst(const fs::FileSnippet& snippet, ExpressionAst& expression);
		FunctionBodyAst(const fs::FileSnippet& snippet, BlockStatementAst& blockStatement);
		FunctionBodyAst(FunctionBodyAst&& other);
		FunctionBodyAst(const FunctionBodyAst&) = delete;
		~FunctionBodyAst() = default;

		const fs::FileSnippet& snippet() const { return _snippet; }
		const auto& isExpression() const { return _isExpression; }
		const auto& expression() const { assert(_isExpression); return *_expression; }
		const auto& blockStatement() const { assert(_blockStatement); return *_blockStatement; }
	};
}

#endif
