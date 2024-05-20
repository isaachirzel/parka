#include "parka/ast/FunctionBodyAst.hpp"

namespace parka::ast
{
	FunctionBodyAst::FunctionBodyAst(const Snippet& snippet, ExpressionAst& expression):
		_snippet(snippet),
		_expression(&expression),
		_isExpression(true)
	{}

	FunctionBodyAst::FunctionBodyAst(const Snippet& snippet, BlockStatementAst& blockStatement):
		_snippet(snippet),
		_blockStatement(&blockStatement),
		_isExpression(false)
	{}

	FunctionBodyAst::FunctionBodyAst(FunctionBodyAst&& other):
		_snippet(other._snippet),
		_isExpression(other._isExpression)
	{
		if (other._isExpression)
		{
			_expression = other._expression;
		}
		else
		{
			_blockStatement = other._blockStatement;
		}
	}
}
