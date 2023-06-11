#ifndef PARKA_SYNTAX_EXPRESSION_CALL_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_CALL_SYNTAX_HPP

#include "parka/syntax/ExpressionSyntax.hpp"

namespace parka
{
	class CallExpressionSyntax : public ExpressionSyntax
	{
		ExpressionSyntax& _primary;
		Array<ExpressionSyntax*> _arguments;

	public:

		CallExpressionSyntax(ExpressionSyntax& primary, Array<ExpressionSyntax*>&& arguments) :
		_primary(primary),
		_arguments(std::move(arguments))
		{}
		CallExpressionSyntax(CallExpressionSyntax&&) = default;
		CallExpressionSyntax(const CallExpressionSyntax&) = delete;

		static ExpressionSyntax *parse(Token& token, ExpressionSyntax& primary);

		ExpressionType expressionType() const { return ExpressionType::Call; }
		const auto& arguments() const { return _arguments; }
	};
}

#endif
