#ifndef PARKA_SYNTAX_EXPRESSION_CALL_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_CALL_SYNTAX_HPP

#include "parka/syntax/ExpressionSyntax.hpp"

namespace parka
{
	class CallExpressionSyntax : public ExpressionSyntax
	{
		ExpressionSyntaxId _primary;
		Array<ExpressionSyntaxId> _arguments;

		CallExpressionSyntax(ExpressionSyntaxId&& primary, Array<ExpressionSyntaxId>&& arguments) :
		_primary(std::move(primary)),
		_arguments(std::move(arguments))
		{}

	public:

		CallExpressionSyntax(CallExpressionSyntax&&) = default;
		CallExpressionSyntax(const CallExpressionSyntax&) = delete;
		~CallExpressionSyntax() = default;

		static Optional<ExpressionSyntaxId> parse(Token& token, ExpressionSyntaxId primary);

		const auto& arguments() const { return _arguments; }
	};
}

#endif
