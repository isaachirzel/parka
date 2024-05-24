#ifndef PARKA_EVALUATION_GLOBAL_STATE_HPP
#define PARKA_EVALUATION_GLOBAL_STATE_HPP

#include "parka/enum/BinaryExpressionType.hpp"
#include "parka/evaluation/IntrinsicBinaryOperator.hpp"
#include "parka/evaluation/IntrinsicConversion.hpp"
#include "parka/evaluation/Value.hpp"
#include "parka/ir/LValueIr.hpp"
#include "parka/symbol/BinaryOperatorKey.hpp"
#include "parka/symbol/ConversionKey.hpp"
#include "parka/util/FlatMap.hpp"

namespace parka::evaluation
{
	class GlobalState
	{
		FlatMap<ConversionKey, IntrinsicConversion> _intrinsicConversions;
		FlatMap<BinaryOperatorKey, IntrinsicBinaryOperator> _intrinsicBinaryOperators;

	public:

		GlobalState();
		GlobalState(GlobalState&&) = default;
		GlobalState(const GlobalState&) = delete;

		Value& add(ir::LValueIr *key, const ir::TypeIr& type);

		IntrinsicConversion getConversion(const ir::TypeIr& to, const ir::TypeIr& from) const;
		IntrinsicBinaryOperator getBinaryOperator(const ir::TypeIr& left, const ir::TypeIr& right, BinaryExpressionType binaryExpressionType) const;
	};
}

#endif
