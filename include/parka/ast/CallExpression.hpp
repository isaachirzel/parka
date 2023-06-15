#ifndef PARKA_SYNTAX_EXPRESSION_CALL_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_CALL_SYNTAX_HPP

#include "parka/ast/Expression.hpp"

namespace parka
{
	class CallExpressionSyntax : public ExpressionSyntax
	{
		ExpressionSyntax& _primary;
		Array<ExpressionSyntax*> _arguments;

	public:

		CallExpressionSyntax(ExpressionSyntax& primary, Array<ExpressionSyntax*>&& arguments);
		CallExpressionSyntax(CallExpressionSyntax&&) = default;
		CallExpressionSyntax(const CallExpressionSyntax&) = delete;

		static ExpressionSyntax *parse(Token& token, ExpressionSyntax& primary);
		ExpressionContext *validate(SymbolTable& symbolTable);

		ExpressionType expressionType() const { return ExpressionType::Call; }
		const auto& arguments() const { return _arguments; }
	};
}

#endif