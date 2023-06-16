#ifndef PARKA_SYNTAX_EXPRESSION_CALL_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_CALL_SYNTAX_HPP

#include "parka/ast/Expression.hpp"

namespace parka
{
	class CallExpressionSyntax : public ExpressionSyntax
	{
		Snippet _snippet;
		ExpressionSyntax& _primary;
		Array<ExpressionSyntax*> _arguments;

	public:

		CallExpressionSyntax(const Snippet& snippet, ExpressionSyntax& primary, Array<ExpressionSyntax*>&& arguments) :
		_snippet(snippet),
		_primary(primary),
		_arguments(std::move(arguments))
		{}
		CallExpressionSyntax(CallExpressionSyntax&&) = default;
		CallExpressionSyntax(const CallExpressionSyntax&) = delete;

		static ExpressionSyntax *parse(Token& token, ExpressionSyntax& primary);
		ExpressionContext *validate(SymbolTable& symbolTable);

		const Snippet& snippet() const { return _snippet; }
		ExpressionType expressionType() const { return ExpressionType::Call; }
		const auto& arguments() const { return _arguments; }
	};
}

#endif
