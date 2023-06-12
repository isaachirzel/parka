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
		AdditiveType _type;

	public:

		AdditiveExpressionContext(ExpressionContext& lhs, ExpressionContext& rhs, AdditiveType type);
		AdditiveExpressionContext(AdditiveExpressionContext&&) = default;
		AdditiveExpressionContext(const AdditiveExpressionContext&) = delete;

		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
		const auto& type() const { return _type; }
	};
}

#endif
