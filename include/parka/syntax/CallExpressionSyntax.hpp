#ifndef PARKA_SYNTAX_EXPRESSION_CALL_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_CALL_SYNTAX_HPP

#include "parka/syntax/ExpressionSyntax.hpp"

namespace parka
{
	class CallExpressionSyntax : public ExpressionSyntax
	{
		const ExpressionSyntax& _primary;
		Array<const ExpressionSyntax*> _arguments;

		CallExpressionSyntax(const ExpressionSyntax& primary, Array<const ExpressionSyntax*>&& arguments) :
		_primary(primary),
		_arguments(std::move(arguments))
		{}

	public:

		CallExpressionSyntax(CallExpressionSyntax&&) = default;
		CallExpressionSyntax(const CallExpressionSyntax&) = delete;

		static const ExpressionSyntax *parse(Token& token, const ExpressionSyntax& primary);

		ExpressionType expressionType() const { return ExpressionType::Call; }
		const auto& arguments() const { return _arguments; }
	};
}

#endif
