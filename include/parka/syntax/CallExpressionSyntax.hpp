#ifndef PARKA_SYNTAX_EXPRESSION_CALL_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_CALL_SYNTAX_HPP

#include "parka/syntax/ExpressionSyntax.hpp"

namespace parka
{
	class CallExpressionSyntax : public ExpressionSyntax
	{
		ExpressionId _primary;
		Array<ExpressionId> _arguments;

		CallExpressionSyntax(ExpressionId&& primary, Array<ExpressionId>&& arguments) :
		_primary(std::move(primary)),
		_arguments(std::move(arguments))
		{}

	public:

		CallExpressionSyntax(CallExpressionSyntax&&) = default;
		CallExpressionSyntax(const CallExpressionSyntax&) = delete;
		~CallExpressionSyntax() = default;

		static Optional<ExpressionId> parse(Token& token, ExpressionId primary);

		const auto& arguments() const { return _arguments; }
	};
}

#endif
