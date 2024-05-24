#ifndef PARKA_EVALUATION_GLOBAL_STATE_HPP
#define PARKA_EVALUATION_GLOBAL_STATE_HPP

#include "parka/enum/AssignmentType.hpp"
#include "parka/enum/BinaryExpressionType.hpp"
#include "parka/evaluation/IntrinsicAssignmentOperator.hpp"
#include "parka/evaluation/IntrinsicBinaryOperator.hpp"
#include "parka/evaluation/IntrinsicConversion.hpp"
#include "parka/evaluation/Value.hpp"
#include "parka/ir/LValueIr.hpp"
#include "parka/symbol/AssignmentOperatorKey.hpp"
#include "parka/symbol/BinaryOperatorKey.hpp"
#include "parka/symbol/ConversionKey.hpp"
#include "parka/util/FlatMap.hpp"

namespace parka::evaluation
{
	class GlobalState
	{
		FlatMap<BinaryOperatorKey, IntrinsicBinaryOperator> _intrinsicBinaryOperators;
		FlatMap<AssignmentOperatorKey, IntrinsicAssignmentOperator> _intrinsicAssignmentOperators;
		FlatMap<ConversionKey, IntrinsicConversion> _intrinsicConversions;

	public:

		GlobalState();
		GlobalState(GlobalState&&) = default;
		GlobalState(const GlobalState&) = delete;

		Value& add(ir::LValueIr *key, const ir::TypeIr& type);

		IntrinsicBinaryOperator getBinaryOperator(const ir::TypeIr& left, const ir::TypeIr& right, BinaryExpressionType binaryExpressionType) const;
		IntrinsicAssignmentOperator getAssignmentOperator(const ir::TypeIr& left, const ir::TypeIr& right, AssignmentType assignmentType) const;
		IntrinsicConversion getConversion(const ir::TypeIr& to, const ir::TypeIr& from) const;
	};
}

#endif
