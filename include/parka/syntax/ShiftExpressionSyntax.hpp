#ifndef PARKA_SYNTAX_EXPRESSION_SHIFT_SYNTAX_HPP
#define PARKA_SYNTAX_EXPRESSION_SHIFT_SYNTAX_HPP

#include "parka/syntax/ExpressionSyntax.hpp"

namespace parka
{
	enum class ShiftType
	{
		Left,
		Right
	};

	class ShiftExpressionSyntax : public ExpressionSyntax
	{
		ExpressionId _lhs;
		ExpressionId _rhs;
		ShiftType _type;

		ShiftExpressionSyntax(ExpressionId&& lhs, ExpressionId&& rhs, ShiftType type) :
		_lhs(std::move(lhs)),
		_rhs(std::move(rhs)),
		_type(type)
		{}

	public:

		ShiftExpressionSyntax(ShiftExpressionSyntax&&) = default;
		ShiftExpressionSyntax(const ShiftExpressionSyntax&) = delete;
		~ShiftExpressionSyntax() = default;

		static Optional<ExpressionId> parse(Token& token);

		bool validate(const EntityId& functionId);
		Optional<Type> getType() const;

		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
	};
}

#endif
