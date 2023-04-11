#ifndef PARKA_SYNTAX_EXPRESSION_RELATIONAL_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_RELATIONAL_SYNTAX_HPP

#include "parka/syntax/ExpressionSyntax.hpp"

namespace parka
{
	enum class RelationalType
	{
		GreaterThan,
		LessThan,
		GreaterThanOrEqualTo,
		LessThanOrEqualTo
	};

	class RelationalExpressionSyntax : public ExpressionSyntax
	{
		ExpressionId _lhs;
		ExpressionId _rhs;
		RelationalType _type;

		RelationalExpressionSyntax(ExpressionId&& lhs, ExpressionId&& rhs, RelationalType type) :
		_lhs(std::move(lhs)),
		_rhs(std::move(rhs)),
		_type(type)
		{}

	public:

		RelationalExpressionSyntax(RelationalExpressionSyntax&&) = default;
		RelationalExpressionSyntax(const RelationalExpressionSyntax&) = delete;
		~RelationalExpressionSyntax() = default;

		static Optional<ExpressionId> parse(Token& token);

		bool validate(const EntityId& functionId);
		Optional<Type> getType() const;

		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
		const auto& type() const { return _type; }
	};
}

#endif
