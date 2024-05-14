#ifndef PARKA_AST_EXPRESSION_CALL_HPP
#define PARKA_AST_EXPRESSION_CALL_HPP

#include "parka/ast/ExpressionAst.hpp"
#include "parka/enum/ExpressionType.hpp"

namespace parka::ast
{
	class CallExpressionAst: public ExpressionAst
	{
		Snippet _snippet;
		ExpressionAst& _subject;
		Array<ExpressionAst*> _arguments;

	public:

		CallExpressionAst(const Snippet& snippet, ExpressionAst& subject, Array<ExpressionAst*>&& arguments):
		ExpressionAst(ExpressionType::Call),
			_snippet(snippet),
			_subject(subject),
			_arguments(std::move(arguments))
		{}
		CallExpressionAst(CallExpressionAst&&) = default;
		CallExpressionAst(const CallExpressionAst&) = delete;

		const Snippet& snippet() const { return _snippet; }
		const auto& subject() const { return _subject; }
		const auto& arguments() const { return _arguments; }
	};
}

#endif
