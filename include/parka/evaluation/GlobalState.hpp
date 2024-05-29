#ifndef PARKA_EVALUATION_GLOBAL_STATE_HPP
#define PARKA_EVALUATION_GLOBAL_STATE_HPP

#include "parka/enum/AssignmentType.hpp"
#include "parka/enum/BinaryExpressionType.hpp"
#include "parka/evaluation/IntrinsicAssignmentOperator.hpp"
#include "parka/evaluation/IntrinsicBinaryOperator.hpp"
#include "parka/evaluation/IntrinsicConversion.hpp"
#include "parka/evaluation/Value.hpp"
#include "parka/ir/EntityIr.hpp"
#include "parka/validation/AssignmentOperatorKey.hpp"
#include "parka/validation/BinaryOperatorKey.hpp"
#include "parka/validation/ConversionKey.hpp"
#include "parka/util/FlatMap.hpp"

namespace parka::evaluation
{
	class GlobalState
	{
		FlatMap<validation::BinaryOperatorKey, IntrinsicBinaryOperator> _intrinsicBinaryOperators;
		FlatMap<validation::AssignmentOperatorKey, IntrinsicAssignmentOperator> _intrinsicAssignmentOperators;
		FlatMap<validation::ConversionKey, IntrinsicConversion> _intrinsicConversions;

	public:

		GlobalState();
		GlobalState(GlobalState&&) = default;
		GlobalState(const GlobalState&) = delete;

		Value& add(ir::EntityIr* key, const ir::TypeIr& type);
	};
}

#endif
