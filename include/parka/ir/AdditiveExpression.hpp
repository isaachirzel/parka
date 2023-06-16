#ifndef PARKA_IR_ADDITIVE_EXPRESSION_HPP
#define PARKA_IR_ADDITIVE_EXPRESSION_HPP

#include "parka/ir/Expression.hpp"
#include "parka/enum/AdditiveType.hpp"
#include "parka/ir/ValueType.hpp"

namespace parka::ir
{
	class AdditiveExpressionIr : public ExpressionIr
	{
		ExpressionIr& _lhs;
		ExpressionIr& _rhs;
		AdditiveType _additiveType;
		ValueType _valueType;

	public:

		AdditiveExpressionIr(ExpressionIr& lhs, ExpressionIr& rhs, AdditiveType additiveType, ValueType&& valueType) :
		ExpressionIr(ExpressionType::Additive),
		_lhs(lhs),
		_rhs(rhs),
		_additiveType(additiveType),
		_valueType(std::move(valueType))
		{}
		AdditiveExpressionIr(AdditiveExpressionIr&&) = default;
		AdditiveExpressionIr(const AdditiveExpressionIr&) = delete;

		const ValueType& valueType() const { return _valueType; }
		const auto& lhs() const { return _lhs; }
		const auto& rhs() const { return _rhs; }
		const auto& additiveType() const { return _additiveType; }
	};
}

#endif
