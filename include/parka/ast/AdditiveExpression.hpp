#ifndef PARKA_SYNTAX_ADDITIVE_EXPRESSION_SYNTAX_HPP
#define PARKA_SYNTAX_ADDITIVE_EXPRESSION_SYNTAX_HPP

#include "parka/ast/Expression.hpp"

namespace parka
{
	enum class AdditiveType
	{
		Add,
		Subtract
	};

	class AdditiveExpressionContext : public ExpressionContext
	{
		ExpressionContext& _lhs;
		ExpressionContext& _rhs;
		AdditiveType _additiveType;
		ValueType _valueType;

	public:

		AdditiveExpressionContext(ExpressionContext& lhs, ExpressionContext& rhs, AdditiveType additiveType, ValueType&& valueType);
		AdditiveExpressionContext(AdditiveExpressionContext&&) = default;
		AdditiveExpressionContext(const AdditiveExpressionContext&) = delete;

		ExpressionType expressionType() const { return ExpressionType::Additive; }
		const ValueType& valueType() const { return _valueType; }
		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
		const auto& additiveType() const { return _additiveType; }
	};

	class AdditiveExpressionSyntax : public ExpressionSyntax
	{
		ExpressionSyntax& _lhs;
		ExpressionSyntax& _rhs;
		AdditiveType _type;
		
	public:

		AdditiveExpressionSyntax(ExpressionSyntax& lhs, ExpressionSyntax& rhs, AdditiveType type);
		AdditiveExpressionSyntax(AdditiveExpressionSyntax&&) = default;
		AdditiveExpressionSyntax(AdditiveExpressionSyntax&) = delete;

		static ExpressionSyntax *parse(Token& token);
		ExpressionContext *validate(SymbolTable& symbolTable);

		ExpressionType expressionType() const { return ExpressionType::Additive; }
		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
		const auto& type() const { return _type; }
	};
}

#endif
