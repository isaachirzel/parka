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

		AdditiveExpressionContext(ExpressionContext& lhs, ExpressionContext& rhs, AdditiveType additiveType, ValueType&& valueType) :
		_lhs(lhs),
		_rhs(rhs),
		_additiveType(additiveType),
		_valueType(std::move(valueType))
		{}
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
		Snippet _snippet;
		ExpressionSyntax& _lhs;
		ExpressionSyntax& _rhs;
		AdditiveType _type;
		
	public:

		AdditiveExpressionSyntax(ExpressionSyntax& lhs, ExpressionSyntax& rhs, AdditiveType type) :
		_snippet(lhs.snippet() + rhs.snippet()),
		_lhs(lhs),
		_rhs(rhs),
		_type(type)
		{}
		AdditiveExpressionSyntax(AdditiveExpressionSyntax&&) = default;
		AdditiveExpressionSyntax(AdditiveExpressionSyntax&) = delete;

		static ExpressionSyntax *parse(Token& token);
		ExpressionContext *validate(SymbolTable& symbolTable);

		const Snippet& snippet() const { return _snippet; }
		ExpressionType expressionType() const { return ExpressionType::Additive; }
		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
		const auto& type() const { return _type; }
	};
}

#endif
