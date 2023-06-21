#ifndef PARKA_AST_EXPRESSION_CALL_HPP
#define PARKA_AST_EXPRESSION_CALL_HPP

#include "parka/ast/Expression.hpp"
#include "parka/enum/ExpressionType.hpp"

namespace parka::ast
{
	class CallExpressionAst : public ExpressionAst
	{
		Snippet _snippet;
		ExpressionAst& _primary;
		Array<ExpressionAst*> _arguments;

	public:

		CallExpressionAst(const Snippet& snippet, ExpressionAst& primary, Array<ExpressionAst*>&& arguments) :
		ExpressionAst(ExpressionType::Call),
		_snippet(snippet),
		_primary(primary),
		_arguments(std::move(arguments))
		{}
		CallExpressionAst(CallExpressionAst&&) = default;
		CallExpressionAst(const CallExpressionAst&) = delete;

		const Snippet& snippet() const { return _snippet; }
		const auto& arguments() const { return _arguments; }
	};
}

#endif
