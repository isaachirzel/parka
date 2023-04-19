#ifndef PARKA_SYNTAX_EXPRESSION_RELATIONAL_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_RELATIONAL_SYNTAX_HPP

#include "parka/enum/RelationalType.hpp"
#include "parka/syntax/ExpressionSyntax.hpp"

namespace parka
{
	class RelationalExpressionSyntax : public ExpressionSyntax
	{
		ExpressionSyntaxId _lhs;
		ExpressionSyntaxId _rhs;
		RelationalType _type;

		RelationalExpressionSyntax(ExpressionSyntaxId&& lhs, ExpressionSyntaxId&& rhs, RelationalType type) :
		_lhs(std::move(lhs)),
		_rhs(std::move(rhs)),
		_type(type)
		{}

	public:

		RelationalExpressionSyntax(RelationalExpressionSyntax&&) = default;
		RelationalExpressionSyntax(const RelationalExpressionSyntax&) = delete;

		static Optional<ExpressionSyntaxId> parse(Token& token);

		bool validate(const EntitySyntaxId& functionId);
		Optional<Type> getType() const;

		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
		const auto& type() const { return _type; }
	};
}

#endif
