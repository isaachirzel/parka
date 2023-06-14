#ifndef PARKA_CONTEXT_ADDITIVE_EXPRESSION_CONTEXT_HPP
#define PARKA_CONTEXT_ADDITIVE_EXPRESSION_CONTEXT_HPP

#include "parka/context/ExpressionContext.hpp"
#include "parka/enum/AdditiveType.hpp"

namespace parka
{
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
}

#endif
